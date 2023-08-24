#include "ComponentHeader.h"

BoxCollider::BoxCollider(const Vector3& p_Size)
	: BoxCollider(p_Size, false, false, 0.1f) {}

BoxCollider::BoxCollider(const Vector3& p_Size, bool p_isPassive)
	: BoxCollider(p_Size, p_isPassive, false, 0.1f) {}

BoxCollider::BoxCollider(const Vector3& p_Size, bool p_isPassive, bool p_isFixedChecking)
	: BoxCollider(p_Size, p_isPassive, p_isFixedChecking, 0.1f) {}

BoxCollider::BoxCollider(const Vector3& p_Size, bool p_isPassive, bool p_isFixedChecking, float p_CheckTime)
    : m_Size(p_Size)
{
	m_isPassive = p_isPassive;
	m_isFixedChecking = p_isFixedChecking;
	m_CheckTime = p_CheckTime;
}

void BoxCollider::Update()
{
	if (m_isPassive) return;

	if (ColliderTimeCheck())
	{
		list<GameObject*>::iterator iter = Var::ColliderObjects.begin();

		while (iter != Var::ColliderObjects.end())
		{
			if (*iter == gameObject)
			{
				++iter;
				continue;
			}

			GameObject* obj = *iter++;
			if (!obj->isActive()) continue;

			BoxCollider* bcollider = GetComponentFromObject(obj, BoxCollider);
			SphereCollider* scollider = GetComponentFromObject(obj, SphereCollider);

			if (bcollider != nullptr && bcollider->m_Transform != nullptr)
			{
				bool result = CollisionCheckBtoB(this, bcollider);
				OnTrigger(bcollider, result);
			}
			else if (scollider != nullptr && scollider->m_Transform != nullptr)
			{
				bool result = CollisionCheckBtoS(this, scollider);
				OnTrigger(scollider, result);
			}
		}
	}

	OnStay();
}