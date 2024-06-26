#include "ComponentHeader.h"

SphereCollider::SphereCollider(const float& p_Radius)
	: SphereCollider(p_Radius, false, false, 0.1f) {}

SphereCollider::SphereCollider(const float& p_Radius, bool p_isPassive)
	: SphereCollider(p_Radius, p_isPassive, false, 0.1f) {}

SphereCollider::SphereCollider(const float& p_Radius, bool p_isPassive, bool p_isFixedChecking)
	: SphereCollider(p_Radius, p_isPassive, p_isFixedChecking, 0.1f) {}

SphereCollider::SphereCollider(const float& p_Radius, bool p_isPassive, bool p_isFixedChecking, float p_CheckTime)
    : m_Radius(p_Radius)
{
	m_isPassive = p_isPassive;
	m_isFixedChecking = p_isFixedChecking;
	m_CheckTime = p_CheckTime;
}

void SphereCollider::Update()
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

			// 이미 충돌체크된 경우 충돌연산을 반복하지 않음
			map<pair<GameObject*, GameObject*>, bool>::iterator var = Var::CollidedObjectsPair.find(make_pair(obj, gameObject));
			if (var != Var::CollidedObjectsPair.end())
			{
				bool result = var->second;
				if (bcollider != nullptr && bcollider->m_Transform != nullptr)
				{
					OnTrigger(bcollider, result);
				}
				else if (scollider != nullptr && scollider->m_Transform != nullptr)
				{
					OnTrigger(scollider, result);
				}

				continue;
			}

			if (bcollider != nullptr && bcollider->m_Transform != nullptr)
			{
				bool result = CollisionCheckBtoS(bcollider, this);
				OnTrigger(bcollider, result);

				Var::CollidedObjectsPair.insert(make_pair(make_pair(gameObject, obj), result));
			}
			else if (scollider != nullptr && scollider->m_Transform != nullptr)
			{
				bool result = CollisionCheckStoS(this, scollider);
				OnTrigger(scollider, result);

				Var::CollidedObjectsPair.insert(make_pair(make_pair(gameObject, obj), result));
			}
		}
	}

	OnStay();
}