#include "ComponentHeader.h"

BoxCollider::BoxCollider(const Vector3& p_Size)
{
	m_Size = p_Size;
}

void BoxCollider::Update()
{
	if (ColliderTimeCheck())
	{
		list<GameObject*>::iterator iter = g_ColliderObjects.begin();

		while (iter != g_ColliderObjects.end())
		{
			if (*iter == gameObject)
			{
				++iter;
				continue;
			}

			GameObject* obj = *iter++;
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