#include "Functions.h"
#include "Raycast.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Transform.h"
#include "Camera.h"

Raycast Raycast::ScreenToWorld(const Vector2& p_Position)
{
	// 뷰포트
	D3DVIEWPORT9 viewport;
	g_pd3dDevice->GetViewport(&viewport);

	// 투영행렬
	Matrix16 matProjection;
	g_pd3dDevice->GetTransform(D3DTS_PROJECTION, &matProjection);

	Raycast r;

	// 방향벡터
	// X = ((+2.0f * 마우스 X좌표) / 뷰포트 넓이 - 1.0f) / 1행 1열
	r.m_Direction.x = ((2.0f * p_Position.x) / viewport.Width - 1.0f) / matProjection._11;
	// Y = ((-2.0f * 마우스 Y좌표) / 뷰포트 높이 + 1.0f) / 2행 2열
	r.m_Direction.y = ((-2.0f * p_Position.y) / viewport.Height + 1.0f) / matProjection._22;
	r.m_Direction.z = 1.0f;

	// 뷰스페이스가 적용되기 전의 좌표가 필요하므로 뷰의 역행렬을 구함
	Matrix16 matView, matInvView;
	g_pd3dDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matInvView, 0, &matView);

	// 뷰의 역행렬로 ray의 출발점과 방향벡터를 변환 및 정규화
	D3DXVec3TransformCoord(&r.m_StartPt, &r.m_StartPt, &matInvView);
	D3DXVec3TransformNormal(&r.m_Direction, &r.m_Direction, &matInvView);
	D3DXVec3Normalize(&r.m_Direction, &r.m_Direction);

	return r;
}

bool Raycast::IsPicked(BoxCollider* p_Collider)
{
	Raycast r = (*this);

	Transform* transform = GetComponentFromObject(p_Collider->gameObject, Transform);
	Vector3 pos = transform->GetWorldPosition();
	Vector3 scale = transform->GetWorldScale();
	Vector3 size = p_Collider->m_Size;
	size.x *= scale.x * 0.5f;
	size.y *= scale.y * 0.5f;
	size.z *= scale.z * 0.5f;

	// 월드의 역행렬
	Matrix16 matInvWorld;
	D3DXMatrixIdentity(&matInvWorld);
	matInvWorld._41 = -pos.x;
	matInvWorld._42 = -pos.y;
	matInvWorld._43 = -pos.z;

	// 카메라의 좌표 및 방향 벡터 변환
	D3DXVec3TransformCoord(&r.m_StartPt, &r.m_StartPt, &matInvWorld);
	D3DXVec3TransformNormal(&r.m_Direction, &r.m_Direction, &matInvWorld);

	Vector3 vertex[8] = {
		Vector3(pos.x - size.x, pos.y + size.y, pos.z + size.z),
		Vector3(pos.x + size.x, pos.y + size.y, pos.z + size.z),
		Vector3(pos.x + size.x, pos.y - size.y, pos.z + size.z),
		Vector3(pos.x - size.x, pos.y - size.y, pos.z + size.z),
		Vector3(pos.x - size.x, pos.y + size.y, pos.z - size.z),
		Vector3(pos.x + size.x, pos.y + size.y, pos.z - size.z),
		Vector3(pos.x + size.x, pos.y - size.y, pos.z - size.z),
		Vector3(pos.x - size.x, pos.y - size.y, pos.z - size.z)
	};

	Vector3 casted;
	if (IntersectTri(vertex[0], vertex[1], vertex[2], casted) ||
		IntersectTri(vertex[2], vertex[3], vertex[0], casted) ||
		IntersectTri(vertex[5], vertex[4], vertex[7], casted) ||
		IntersectTri(vertex[7], vertex[6], vertex[5], casted) ||
		IntersectTri(vertex[1], vertex[5], vertex[6], casted) ||
		IntersectTri(vertex[6], vertex[2], vertex[1], casted) ||
		IntersectTri(vertex[4], vertex[0], vertex[3], casted) ||
		IntersectTri(vertex[3], vertex[7], vertex[4], casted) ||
		IntersectTri(vertex[4], vertex[5], vertex[1], casted) ||
		IntersectTri(vertex[1], vertex[0], vertex[4], casted) ||
		IntersectTri(vertex[3], vertex[2], vertex[6], casted) ||
		IntersectTri(vertex[6], vertex[7], vertex[3], casted))
	{
		return true;
	}

	return false;
}

bool Raycast::IsPicked(SphereCollider* p_Collider)
{
	Raycast r = (*this);

	Transform* transform = GetComponentFromObject(p_Collider->gameObject, Transform);
	Vector3 pos = transform->GetWorldPosition();
	Vector3 scale = transform->GetWorldScale();
	float rate = (scale.x + scale.y + scale.z) * 0.33333f;

	// 월드의 역행렬
	Matrix16 matInvWorld;
	D3DXMatrixIdentity(&matInvWorld);
	matInvWorld._41 = -pos.x;
	matInvWorld._42 = -pos.y;
	matInvWorld._43 = -pos.z;

	// 카메라의 좌표 및 방향 벡터 변환
	D3DXVec3TransformCoord(&r.m_StartPt, &r.m_StartPt, &matInvWorld);
	D3DXVec3TransformNormal(&r.m_Direction, &r.m_Direction, &matInvWorld);

	float vv = D3DXVec3Dot(&r.m_Direction, &r.m_Direction);
	float qv = D3DXVec3Dot(&r.m_StartPt, &r.m_Direction);
	float qq = D3DXVec3Dot(&r.m_StartPt, &r.m_StartPt);
	float rr = (p_Collider->m_Radius * rate) * (p_Collider->m_Radius * rate);

	// =0: 1개점 교차
	// >0: 2개점 교차
	// <0: 교차하지 않음
	return qv * qv - vv * (qq - rr) >= 0;
}

bool Raycast::IntersectTri(const Vector3& p_V0, const Vector3& p_V1, const Vector3& p_V2, Vector3& p_Result)
{
	// verteice 3개를 잇는 면이 충돌하는 지 판정
	float u, v, t;
	bool b = D3DXIntersectTri(&p_V0, &p_V1, &p_V2, &m_StartPt, &m_Direction, &u, &v, &t);
	p_Result = m_StartPt + (t * m_Direction);
	//p_Result = p_Pos0 + (u * (p_V1 - p_V0)) + (v * (p_V2 - p_V0));

	return b;
}