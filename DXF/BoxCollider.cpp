#include "ComponentHeader.h"

BoxCollider::BoxCollider(Vector3 _size)
{
	size = _size;
}

void BoxCollider::Update()
{
	list<SPTR<GameObject>>::iterator iter = g_Objects.begin();

	while (iter != g_Objects.end())
	{
		if (*iter == gameObject)
		{
			++iter;
			continue;
		}

		GameObject* obj = (*iter++)();

		Transform* objtransform = GetComponentFromObject(obj, Transform);
		BoxCollider* bcollider = GetComponentFromObject(obj, BoxCollider);
		SphereCollider* scollider = GetComponentFromObject(obj, SphereCollider);

		if (objtransform == nullptr) continue;
		if (bcollider != nullptr)
		{
			bool result = CollisionCheckBtoB(this, bcollider);
			OnTrigger(bcollider, result);
		}
		else if (scollider != nullptr)
		{
			bool result = CollisionCheckBtoS(this, scollider);
			OnTrigger(scollider, result);
		}
	}

	OnStay();
}