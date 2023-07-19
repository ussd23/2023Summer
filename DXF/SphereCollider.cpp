#include "ComponentHeader.h"

SphereCollider::SphereCollider(const float& p_Radius)
{
	m_Radius = p_Radius;
}

void SphereCollider::Update()
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
				bool result = CollisionCheckBtoS(bcollider, this);
				OnTrigger(bcollider, result);
			}
			else if (scollider != nullptr && scollider->m_Transform != nullptr)
			{
				bool result = CollisionCheckStoS(this, scollider);
				OnTrigger(scollider, result);
			}
		}
	}

	OnStay();
}