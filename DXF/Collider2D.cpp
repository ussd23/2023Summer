#include "ComponentHeader.h"

void Collider2D::Start()
{
	m_RectTransform = GetComponentFromObject(gameObject, RectTransform);

	m_PreSecond = (rand() / (float)RAND_MAX) * m_CheckTime;
}

bool Collider2D::GetSeparatingPlane(Vector2 p_RPos, Vector2 p_Plane, BoxCollider2D* p_Col1, BoxCollider2D* p_Col2)
{
	Vector2 vDot[4];
	vDot[0] = p_Col1->m_AxisX * p_Col1->m_HalfSize.x;
	vDot[1] = p_Col1->m_AxisY * p_Col1->m_HalfSize.y;
	vDot[2] = p_Col2->m_AxisX * p_Col2->m_HalfSize.x;
	vDot[3] = p_Col2->m_AxisY * p_Col2->m_HalfSize.y;

	return (fabs(D3DXVec2Dot(&p_RPos, &p_Plane)) >
			(fabs(D3DXVec2Dot(&vDot[0], &p_Plane)) +
			fabs(D3DXVec2Dot(&vDot[1], &p_Plane)) +
			fabs(D3DXVec2Dot(&vDot[2], &p_Plane)) +
			fabs(D3DXVec2Dot(&vDot[3], &p_Plane))));
}

bool Collider2D::CollisionCheckBtoB(BoxCollider2D* p_Col1, BoxCollider2D* p_Col2)
{
	if (!p_Col1->gameObject->isActive() || !p_Col2->gameObject->isActive()) return false;

	Vector2 pos1 = p_Col1->m_RectTransform->GetScreenPosition();
	Vector2 pos2 = p_Col2->m_RectTransform->GetScreenPosition();

	Vector2 rPos;
	rPos = pos2 - pos1;

	return !(GetSeparatingPlane(rPos, p_Col1->m_AxisX, p_Col1, p_Col2) ||
		GetSeparatingPlane(rPos, p_Col1->m_AxisY, p_Col1, p_Col2) ||
		GetSeparatingPlane(rPos, p_Col2->m_AxisX, p_Col1, p_Col2) ||
		GetSeparatingPlane(rPos, p_Col2->m_AxisY, p_Col1, p_Col2));
}

bool Collider2D::CollisionCheckBtoS(BoxCollider2D* p_Col1, SphereCollider2D* p_Col2)
{
	if (!p_Col1->gameObject->isActive() || !p_Col2->gameObject->isActive()) return false;

	Vector2 pos1 = p_Col1->m_RectTransform->GetScreenPosition();
	Vector3 rot1 = Functions::QuaternionToEuler(p_Col1->m_RectTransform->GetScreenRotation());
	Vector2 size = p_Col1->m_RectTransform->GetScreenScale();
	Vector2 size1 = p_Col1->m_Size;
	size1.x *= size.x * 0.5f;
	size1.y *= size.y * 0.5f;

	Vector2 col1min = pos1 - size1;
	Vector2 col1max = pos1 + size1;

	Vector2 pos2 = p_Col2->m_RectTransform->GetScreenPosition();
	Quaternion rot2 = Functions::EulerToQuaternion(-rot1);
	pos2 = Functions::VectorRotate(rot2, pos2 - pos1) + pos1;
	Vector2 scale = p_Col2->m_RectTransform->GetScreenScale();
	float rate = (scale.x + scale.y) * 0.5f;
	float length = rate * p_Col2->m_Radius;

	Vector2 closepoint;

	if (pos2.x < pos1.x - size1.x) closepoint.x = pos1.x - size1.x;
	else if (pos2.x > pos1.x + size1.x)	closepoint.x = pos1.x + size1.x;
	else closepoint.x = pos2.x;

	if (pos2.y < pos1.y - size1.y) closepoint.y = pos1.y - size1.y;
	else if (pos2.y > pos1.y + size1.y)	closepoint.y = pos1.y + size1.y;
	else closepoint.y = pos2.y;

	return Functions::GetDistanceSquare(pos2, closepoint) < length * length;
}

bool Collider2D::CollisionCheckStoS(SphereCollider2D* p_Col1, SphereCollider2D* p_Col2)
{
	if (!p_Col1->gameObject->isActive() || !p_Col2->gameObject->isActive()) return false;

	float distance = Functions::GetDistanceSquare(p_Col1->m_RectTransform->GetScreenPosition(), p_Col2->m_RectTransform->GetScreenPosition());

	Vector2 scale = p_Col1->m_RectTransform->GetScreenScale();
	float rate1 = (scale.x + scale.y) * 0.5f;
	scale = p_Col2->m_RectTransform->GetScreenScale();
	float rate2 = (scale.x + scale.y) * 0.5f;
	float limitlength = p_Col1->m_Radius * rate1 + p_Col2->m_Radius * rate2;

	return limitlength * limitlength > distance;
}