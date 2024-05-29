#include "ComponentHeader.h"

BoxCollider2D::BoxCollider2D(const Vector2& p_Size)
	: BoxCollider2D(p_Size, false, false, 0.1f) {}

BoxCollider2D::BoxCollider2D(const Vector2& p_Size, bool p_isPassive)
	: BoxCollider2D(p_Size, p_isPassive, false, 0.1f) {}

BoxCollider2D::BoxCollider2D(const Vector2& p_Size, bool p_isPassive, bool p_isFixedChecking)
	: BoxCollider2D(p_Size, p_isPassive, p_isFixedChecking, 0.1f) {}

BoxCollider2D::BoxCollider2D(const Vector2& p_Size, bool p_isPassive, bool p_isFixedChecking, float p_CheckTime)
	: m_Size(p_Size)
{
	m_isPassive = p_isPassive;
	m_isFixedChecking = p_isFixedChecking;
	m_CheckTime = p_CheckTime;
}

void BoxCollider2D::PreUpdate()
{
	Quaternion rot = m_RectTransform->GetScreenRotation();
	Vector2 size = m_RectTransform->GetScreenScale();
	m_HalfSize = m_Size;
	m_HalfSize.x *= size.x * 0.5f;
	m_HalfSize.y *= size.y * 0.5f;

	m_AxisX = Functions::VectorRotate(rot, Vector2(1, 0));
	m_AxisY = Functions::VectorRotate(rot, Vector2(0, 1));
}

void BoxCollider2D::Update()
{
	if (m_isPassive) return;

	if (ColliderTimeCheck())
	{
		list<GameObject*>::iterator iter = Var::Collider2DObjects.begin();

		while (iter != Var::Collider2DObjects.end())
		{
			if (*iter == gameObject)
			{
				++iter;
				continue;
			}

			GameObject* obj = *iter++;
			if (!obj->isActive()) continue;

			BoxCollider2D* bcollider = GetComponentFromObject(obj, BoxCollider2D);
			SphereCollider2D* scollider = GetComponentFromObject(obj, SphereCollider2D);

			// 이미 충돌체크된 경우 충돌연산을 반복하지 않음
			map<pair<GameObject*, GameObject*>, bool>::iterator var = Var::CollidedObjectsPair.find(make_pair(obj, gameObject));
			if (var != Var::CollidedObjectsPair.end())
			{
				bool result = var->second;
				if (bcollider != nullptr && bcollider->m_RectTransform != nullptr)
				{
					OnTrigger(bcollider, result);
				}
				else if (scollider != nullptr && scollider->m_RectTransform != nullptr)
				{
					OnTrigger(scollider, result);
				}

				continue;
			}

			if (bcollider != nullptr && bcollider->m_RectTransform != nullptr)
			{
				bool result = CollisionCheckBtoB(this, bcollider);
				OnTrigger(bcollider, result);

				Var::CollidedObjectsPair.insert(make_pair(make_pair(gameObject, obj), result));
			}
			else if (scollider != nullptr && scollider->m_RectTransform != nullptr)
			{
				bool result = CollisionCheckBtoS(this, scollider);
				OnTrigger(scollider, result);

				Var::CollidedObjectsPair.insert(make_pair(make_pair(gameObject, obj), result));
			}
		}
	}

	OnStay();
}