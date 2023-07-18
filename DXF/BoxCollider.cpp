#include "ComponentHeader.h"

BoxCollider::BoxCollider(Vector3 _size)
{
	size = _size;
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

			if (bcollider != nullptr && bcollider->transform != nullptr)
			{
				bool result = CollisionCheckBtoB(this, bcollider);
				OnTrigger(bcollider, result);
			}
			else if (scollider != nullptr && scollider->transform != nullptr)
			{
				bool result = CollisionCheckBtoS(this, scollider);
				OnTrigger(scollider, result);
			}
		}
	}

	OnStay();
}