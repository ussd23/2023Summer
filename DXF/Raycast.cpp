#include "Functions.h"
#include "Raycast.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Transform.h"
#include "Camera.h"

Raycast Raycast::ScreenToWorld(D3DXVECTOR2 _pos)
{
	// 뷰포트
	D3DVIEWPORT9 viewport;
	g_pd3dDevice->GetViewport(&viewport);

	// 투영행렬
	D3DXMATRIXA16 matProjection;
	g_pd3dDevice->GetTransform(D3DTS_PROJECTION, &matProjection);

	Raycast r;

	// 방향벡터
	// X = ((+2.0f * 마우스 X좌표) / 뷰포트 넓이 - 1.0f) / 1행 1열
	r.vDirection.x = ((2.0f * _pos.x) / viewport.Width - 1.0f) / matProjection._11;
	// Y = ((-2.0f * 마우스 Y좌표) / 뷰포트 높이 + 1.0f) / 2행 2열
	r.vDirection.y = ((-2.0f * _pos.y) / viewport.Height + 1.0f) / matProjection._22;
	r.vDirection.z = 1.0f;

	// 뷰스페이스가 적용되기 전의 좌표가 필요하므로 뷰의 역행렬을 구함
	D3DXMATRIXA16 matView, matInvView;
	g_pd3dDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matInvView, 0, &matView);

	// 뷰의 역행렬로 ray의 출발점과 방향벡터를 변환 및 정규화
	D3DXVec3TransformCoord(&r.vStartPt, &r.vStartPt, &matInvView);
	D3DXVec3TransformNormal(&r.vDirection, &r.vDirection, &matInvView);
	D3DXVec3Normalize(&r.vDirection, &r.vDirection);

	return r;
}

bool Raycast::IsPicked(BoxCollider* _collider)
{
	Raycast r = (*this);

	Transform* transform = GetComponentFromObject(_collider->gameObject, Transform);
	D3DXVECTOR3 pos = transform->GetWorldPosition();
	D3DXVECTOR3 scale = transform->GetWorldScale();
	D3DXVECTOR3 size = _collider->size;
	size.x *= scale.x / 2;
	size.y *= scale.y / 2;
	size.z *= scale.z / 2;

	// 월드의 역행렬
	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixIdentity(&matInvWorld);
	matInvWorld._41 = -pos.x;
	matInvWorld._42 = -pos.y;
	matInvWorld._43 = -pos.z;

	// 카메라의 좌표 및 방향 벡터 변환
	D3DXVec3TransformCoord(&r.vStartPt, &r.vStartPt, &matInvWorld);
	D3DXVec3TransformNormal(&r.vDirection, &r.vDirection, &matInvWorld);

	D3DXVECTOR3 vertex[8] = {
		D3DXVECTOR3(pos.x - size.x, pos.y + size.y, pos.z + size.z),
		D3DXVECTOR3(pos.x + size.x, pos.y + size.y, pos.z + size.z),
		D3DXVECTOR3(pos.x + size.x, pos.y - size.y, pos.z + size.z),
		D3DXVECTOR3(pos.x - size.x, pos.y - size.y, pos.z + size.z),
		D3DXVECTOR3(pos.x - size.x, pos.y + size.y, pos.z - size.z),
		D3DXVECTOR3(pos.x + size.x, pos.y + size.y, pos.z - size.z),
		D3DXVECTOR3(pos.x + size.x, pos.y - size.y, pos.z - size.z),
		D3DXVECTOR3(pos.x - size.x, pos.y - size.y, pos.z - size.z)
	};

	D3DXVECTOR3 casted;
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

bool Raycast::IsPicked(SphereCollider* _collider)
{
	Raycast r = (*this);

	Transform* transform = GetComponentFromObject(_collider->gameObject, Transform);
	D3DXVECTOR3 pos = transform->GetWorldPosition();
	D3DXVECTOR3 scale = transform->GetWorldScale();
	float rate = (scale.x + scale.y + scale.z) / 3.f;

	// 월드의 역행렬
	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixIdentity(&matInvWorld);
	matInvWorld._41 = -pos.x;
	matInvWorld._42 = -pos.y;
	matInvWorld._43 = -pos.z;

	// 카메라의 좌표 및 방향 벡터 변환
	D3DXVec3TransformCoord(&r.vStartPt, &r.vStartPt, &matInvWorld);
	D3DXVec3TransformNormal(&r.vDirection, &r.vDirection, &matInvWorld);

	float vv = D3DXVec3Dot(&r.vDirection, &r.vDirection);
	float qv = D3DXVec3Dot(&r.vStartPt, &r.vDirection);
	float qq = D3DXVec3Dot(&r.vStartPt, &r.vStartPt);
	float rr = (_collider->radius * rate) * (_collider->radius * rate);

	// =0: 1개점 교차
	// >0: 2개점 교차
	// <0: 교차하지 않음
	return qv * qv - vv * (qq - rr) >= 0;
}

bool Raycast::IntersectTri(D3DXVECTOR3& v0, D3DXVECTOR3& v1, D3DXVECTOR3& v2, D3DXVECTOR3& vposition)
{
	// verteice 3개를 잇는 면이 충돌하는 지 판정(?)
	float u, v, t;
	bool b = D3DXIntersectTri(&v0, &v1, &v2, &vStartPt, &vDirection, &u, &v, &t);
	vposition = vStartPt + (t * vDirection);
	//vposition = v0 + (u * (v1 - v0)) + (v * (v2 - v0));

	return b;
}