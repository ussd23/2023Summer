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

void BoxCollider::PreUpdate()
{
	Quaternion rot = m_Transform->GetWorldRotation();
	Vector3 size = m_Transform->GetWorldScale();
	m_HalfSize = m_Size;
	m_HalfSize.x *= size.x * 0.5f;
	m_HalfSize.y *= size.y * 0.5f;
	m_HalfSize.z *= size.z * 0.5f;
	m_AxisX = Functions::VectorRotate(rot, Vector3(1, 0, 0));
	m_AxisY = Functions::VectorRotate(rot, Vector3(0, 1, 0));
	m_AxisZ = Functions::VectorRotate(rot, Vector3(0, 0, 1));
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

			// 이미 충돌체크된 경우 충돌연산을 반복하지 않음
			map<pair<GameObject*, GameObject*>, bool>::iterator var = Var::CollidedObjectsPair.find(make_pair(gameObject, obj));
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
				bool result = CollisionCheckBtoB(this, bcollider);
				OnTrigger(bcollider, result);

				Var::CollidedObjectsPair.insert(make_pair(make_pair(gameObject, obj), result));
			}
			else if (scollider != nullptr && scollider->m_Transform != nullptr)
			{
				bool result = CollisionCheckBtoS(this, scollider);
				OnTrigger(scollider, result);

				Var::CollidedObjectsPair.insert(make_pair(make_pair(gameObject, obj), result));
			}
		}
	}

	OnStay();
}