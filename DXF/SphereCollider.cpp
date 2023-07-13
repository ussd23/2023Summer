#include "ComponentHeader.h"

SphereCollider::SphereCollider(float _radius)
{
	radius = _radius;
}

void SphereCollider::Update()
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
			bool result = CollisionCheckBtoS(bcollider, this);
			OnTrigger(bcollider, result);
		}
		else if (scollider != nullptr)
		{
			bool result = CollisionCheckStoS(this, scollider);
			OnTrigger(scollider, result);
		}
	}
	OnStay();
}