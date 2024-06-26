#include "ComponentHeader.h"

void Collider::Start()
{
	m_Transform = GetComponentFromObject(gameObject, Transform);

	m_PreSecond = (rand() / (float)RAND_MAX) * m_CheckTime;
}

bool Collider::ColliderTimeCheck()
{
	if (!m_isFixedChecking) return true;

	m_PreSecond += Time::deltaTime;
	if (m_PreSecond < m_CheckTime)
	{
		return false;
	}
	m_PreSecond -= m_CheckTime;
	return true;
}

void Collider::OnTrigger(Collider* p_Collider, bool p_Result)
{
	map<Collider*, bool>::iterator iter = m_Entering.find(p_Collider);
	if (iter == m_Entering.end())
	{
		m_Entering.insert(make_pair(p_Collider, p_Result));
	}

	if (p_Result != m_Entering[p_Collider])
	{
		m_Entering[p_Collider] = !m_Entering[p_Collider];

		if (m_Entering[p_Collider])
		{
			list<SPTR<Component>>::iterator iter = gameObject->m_Components.begin();

			while (iter != gameObject->m_Components.end())
			{
				(*iter++)->OnTriggerEnter(p_Collider);
			}
		}
		else
		{
			list<SPTR<Component>>::iterator iter = gameObject->m_Components.begin();

			while (iter != gameObject->m_Components.end())
			{
				(*iter++)->OnTriggerExit(p_Collider);
			}
		}
	}
}

void Collider::OnStay()
{
	map<Collider*, bool>::iterator iter = m_Entering.begin();
	while (iter != m_Entering.end())
	{
		if (iter->second)
		{
			list<SPTR<Component>>::iterator citer = gameObject->m_Components.begin();

			while (citer != gameObject->m_Components.end())
			{
				(*citer++)->OnTriggerStay(iter->first);
			}
		}
		++iter;
	}
}

bool Collider::GetSeparatingPlane(Vector3 p_RPos, Vector3 p_Plane, BoxCollider* p_Col1, BoxCollider* p_Col2)
{
	Vector3 vDot[6];
	vDot[0] = p_Col1->m_AxisX * p_Col1->m_HalfSize.x;
	vDot[1] = p_Col1->m_AxisY * p_Col1->m_HalfSize.y;
	vDot[2] = p_Col1->m_AxisZ * p_Col1->m_HalfSize.z;
	vDot[3] = p_Col2->m_AxisX * p_Col2->m_HalfSize.x;
	vDot[4] = p_Col2->m_AxisY * p_Col2->m_HalfSize.y;
	vDot[5] = p_Col2->m_AxisZ * p_Col2->m_HalfSize.z;

	return (fabs(D3DXVec3Dot(&p_RPos, &p_Plane)) >
			(fabs(D3DXVec3Dot(&vDot[0], &p_Plane)) +
			fabs(D3DXVec3Dot(&vDot[1], &p_Plane)) +
			fabs(D3DXVec3Dot(&vDot[2], &p_Plane)) +
			fabs(D3DXVec3Dot(&vDot[3], &p_Plane)) +
			fabs(D3DXVec3Dot(&vDot[4], &p_Plane)) +
			fabs(D3DXVec3Dot(&vDot[5], &p_Plane))));
}

bool Collider::CollisionCheckBtoB(BoxCollider* p_Col1, BoxCollider* p_Col2)
{
	if (!p_Col1->gameObject->isActive() || !p_Col2->gameObject->isActive()) return false;

	Vector3 pos1 = p_Col1->m_Transform->GetWorldPosition();
	Vector3 pos2 = p_Col2->m_Transform->GetWorldPosition();

	Vector3 rPos;
	rPos = pos2 - pos1;

	Vector3 vCross[9];
	D3DXVec3Cross(&vCross[0], &p_Col1->m_AxisX, &p_Col2->m_AxisX);
	D3DXVec3Cross(&vCross[1], &p_Col1->m_AxisX, &p_Col2->m_AxisY);
	D3DXVec3Cross(&vCross[2], &p_Col1->m_AxisX, &p_Col2->m_AxisZ);
	D3DXVec3Cross(&vCross[3], &p_Col1->m_AxisY, &p_Col2->m_AxisX);
	D3DXVec3Cross(&vCross[4], &p_Col1->m_AxisY, &p_Col2->m_AxisY);
	D3DXVec3Cross(&vCross[5], &p_Col1->m_AxisY, &p_Col2->m_AxisZ);
	D3DXVec3Cross(&vCross[6], &p_Col1->m_AxisZ, &p_Col2->m_AxisX);
	D3DXVec3Cross(&vCross[7], &p_Col1->m_AxisZ, &p_Col2->m_AxisY);
	D3DXVec3Cross(&vCross[8], &p_Col1->m_AxisZ, &p_Col2->m_AxisZ);

	return !(GetSeparatingPlane(rPos, p_Col1->m_AxisX, p_Col1, p_Col2) ||
		GetSeparatingPlane(rPos, p_Col1->m_AxisY, p_Col1, p_Col2) ||
		GetSeparatingPlane(rPos, p_Col1->m_AxisZ, p_Col1, p_Col2) ||
		GetSeparatingPlane(rPos, p_Col2->m_AxisX, p_Col1, p_Col2) ||
		GetSeparatingPlane(rPos, p_Col2->m_AxisY, p_Col1, p_Col2) ||
		GetSeparatingPlane(rPos, p_Col2->m_AxisZ, p_Col1, p_Col2) ||
		GetSeparatingPlane(rPos, vCross[0], p_Col1, p_Col2) ||
		GetSeparatingPlane(rPos, vCross[1], p_Col1, p_Col2) ||
		GetSeparatingPlane(rPos, vCross[2], p_Col1, p_Col2) ||
		GetSeparatingPlane(rPos, vCross[3], p_Col1, p_Col2) ||
		GetSeparatingPlane(rPos, vCross[4], p_Col1, p_Col2) ||
		GetSeparatingPlane(rPos, vCross[5], p_Col1, p_Col2) ||
		GetSeparatingPlane(rPos, vCross[6], p_Col1, p_Col2) ||
		GetSeparatingPlane(rPos, vCross[7], p_Col1, p_Col2) ||
		GetSeparatingPlane(rPos, vCross[8], p_Col1, p_Col2));

	//Vector3 col1min = pos1 - size1;
	//Vector3 col1max = pos1 + size1;
	//Vector3 col2min = pos2 - size2;
	//Vector3 col2max = pos2 + size2;

	//if (col1max.x < col2min.x || col1min.x > col2max.x)
	//	return false;
	//if (col1max.y < col2min.y || col1min.y > col2max.y)
	//	return false;
	//if (col1max.z < col2min.z || col1min.z > col2max.z)
	//	return false;

	//return true;
}

bool Collider::CollisionCheckBtoS(BoxCollider* p_Col1, SphereCollider* p_Col2)
{
	if (!p_Col1->gameObject->isActive() || !p_Col2->gameObject->isActive()) return false;

	Vector3 pos1 = p_Col1->m_Transform->GetWorldPosition();
	Vector3 rot1 = Functions::QuaternionToEuler(p_Col1->m_Transform->GetWorldRotation());
	Vector3 size = p_Col1->m_Transform->GetWorldScale();
	Vector3 size1 = p_Col1->m_Size;
	size1.x *= size.x * 0.5f;
	size1.y *= size.y * 0.5f;
	size1.z *= size.z * 0.5f;

	Vector3 col1min = pos1 - size1;
	Vector3 col1max = pos1 + size1;

	Vector3 pos2 = p_Col2->m_Transform->GetWorldPosition();
	Quaternion rot2 = Functions::EulerToQuaternion(-rot1);
	pos2 = Functions::VectorRotate(rot2, pos2 - pos1) + pos1;
	Vector3 scale = p_Col2->m_Transform->GetWorldScale();
	float rate = (scale.x + scale.y + scale.z) * 0.33333f;
	float length = rate * p_Col2->m_Radius;

	Vector3 closepoint;

	if (pos2.x < pos1.x - size1.x) closepoint.x = pos1.x - size1.x;
	else if (pos2.x > pos1.x + size1.x)	closepoint.x = pos1.x + size1.x;
	else closepoint.x = pos2.x;

	if (pos2.y < pos1.y - size1.y) closepoint.y = pos1.y - size1.y;
	else if (pos2.y > pos1.y + size1.y)	closepoint.y = pos1.y + size1.y;
	else closepoint.y = pos2.y;

	if (pos2.z < pos1.z - size1.z) closepoint.z = pos1.z - size1.z;
	else if (pos2.z > pos1.z + size1.z)	closepoint.z = pos1.z + size1.z;
	else closepoint.z = pos2.z;

	return Functions::GetDistanceSquare(pos2, closepoint) < length * length;
}

bool Collider::CollisionCheckStoS(SphereCollider* p_Col1, SphereCollider* p_Col2)
{
	if (!p_Col1->gameObject->isActive() || !p_Col2->gameObject->isActive()) return false;

	float distance = Functions::GetDistanceSquare(p_Col1->m_Transform->GetWorldPosition(), p_Col2->m_Transform->GetWorldPosition());

	Vector3 scale = p_Col1->m_Transform->GetWorldScale();
	float rate1 = (scale.x + scale.y + scale.z) * 0.33333f;
	scale = p_Col2->m_Transform->GetWorldScale();
	float rate2 = (scale.x + scale.y + scale.z) * 0.33333f;
	float limitlength = p_Col1->m_Radius * rate1 + p_Col2->m_Radius * rate2;

	return limitlength * limitlength > distance;
}