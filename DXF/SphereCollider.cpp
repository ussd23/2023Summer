#include "ComponentHeader.h"

SphereCollider::SphereCollider(float _radius)
{
	radius = _radius;
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

			if (bcollider != nullptr && bcollider->transform != nullptr)
			{
				bool result = CollisionCheckBtoS(bcollider, this);
				OnTrigger(bcollider, result);
			}
			else if (scollider != nullptr && scollider->transform != nullptr)
			{
				bool result = CollisionCheckStoS(this, scollider);
				OnTrigger(scollider, result);
			}
		}
	}

	OnStay();
}