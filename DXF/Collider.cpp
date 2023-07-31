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

bool Collider::CollisionCheckBtoB(BoxCollider* p_Col1, BoxCollider* p_Col2)
{
	if (!p_Col1->gameObject->isActive() || !p_Col2->gameObject->isActive()) return false;

	Vector3 pos1 = p_Col1->m_Transform->GetWorldPosition();
	Vector3 size = p_Col1->m_Transform->GetWorldScale();
	Vector3 size1 = p_Col1->m_Size;
	size1.x *= size.x * 0.5f;
	size1.y *= size.y * 0.5f;
	size1.z *= size.z * 0.5f;

	Vector3 pos2 = p_Col2->m_Transform->GetWorldPosition();
	size = p_Col2->m_Transform->GetWorldScale();
	Vector3 size2 = p_Col2->m_Size;
	size2.x *= size.x * 0.5f;
	size2.y *= size.y * 0.5f;
	size2.z *= size.z * 0.5f;

	Vector3 col1min = pos1 - size1;
	Vector3 col1max = pos1 + size1;
	Vector3 col2min = pos2 - size2;
	Vector3 col2max = pos2 + size2;

	if (col1max.x < col2min.x || col1min.x > col2max.x)
		return false;
	if (col1max.y < col2min.y || col1min.y > col2max.y)
		return false;
	if (col1max.z < col2min.z || col1min.z > col2max.z)
		return false;

	return true;
}

bool Collider::CollisionCheckBtoS(BoxCollider* p_Col1, SphereCollider* p_Col2)
{
	if (!p_Col1->gameObject->isActive() || !p_Col2->gameObject->isActive()) return false;

	Vector3 pos1 = p_Col1->m_Transform->GetWorldPosition();
	Vector3 size = p_Col1->m_Transform->GetWorldScale();
	Vector3 size1 = p_Col1->m_Size;
	size1.x *= size.x * 0.5f;
	size1.y *= size.y * 0.5f;
	size1.z *= size.z * 0.5f;

	Vector3 col1min = pos1 - size1;
	Vector3 col1max = pos1 + size1;

	Vector3 pos2 = p_Col2->m_Transform->GetWorldPosition();
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