#include "ComponentHeader.h"

BoxCollider::BoxCollider(Vector3 _size)
{
	size = _size;
}

void BoxCollider::Update()
{
	for (int i = 0; i < g_Objects.size(); ++i)
	{
		if (g_Objects[i] == gameObject) continue;

		Transform* objtransform = GetComponentFromObject(g_Objects[i](), Transform);
		BoxCollider* bcollider = GetComponentFromObject(g_Objects[i](), BoxCollider);
		SphereCollider* scollider = GetComponentFromObject(g_Objects[i](), SphereCollider);

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