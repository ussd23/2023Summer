#include "ComponentHeader.h"

void Collider::Start()
{
	transform = GetComponentFromObject(gameObject, Transform);

	presecond = (rand() / (float)RAND_MAX) * collidertime;
}

bool Collider::ColliderTimeCheck()
{
	presecond += Time::deltaTime;
	if (presecond < collidertime)
	{
		return false;
	}
	presecond -= collidertime;
	return true;
}

void Collider::OnTrigger(Collider* _collider, bool _result)
{
	map<Collider*, bool>::iterator iter = entering.find(_collider);
	if (iter == entering.end())
	{
		entering.insert(make_pair(_collider, _result));
	}

	if (_result != entering[_collider])
	{
		entering[_collider] = !entering[_collider];

		if (entering[_collider])
		{
			list<SPTR<Component>>::iterator iter = gameObject->components.begin();

			while (iter != gameObject->components.end())
			{
				(*iter++)->OnTriggerEnter(_collider);
			}
		}
		else
		{
			list<SPTR<Component>>::iterator iter = gameObject->components.begin();

			while (iter != gameObject->components.end())
			{
				(*iter++)->OnTriggerExit(_collider);
			}
		}
	}
}

void Collider::OnStay()
{
	map<Collider*, bool>::iterator iter = entering.begin();
	while (iter != entering.end())
	{
		if (iter->second)
		{
			list<SPTR<Component>>::iterator citer = gameObject->components.begin();

			while (citer != gameObject->components.end())
			{
				(*citer++)->OnTriggerStay(iter->first);
			}
		}
		++iter;
	}
}

bool Collider::CollisionCheckBtoB(BoxCollider* _col1, BoxCollider* _col2)
{
	if (!_col1->gameObject->isActive() || !_col2->gameObject->isActive()) return false;

	Vector3 pos1 = _col1->transform->GetWorldPosition();
	Vector3 size = _col1->transform->GetWorldScale();
	Vector3 size1 = _col1->size;
	size1.x *= size.x / 2;
	size1.y *= size.y / 2;
	size1.z *= size.z / 2;

	Vector3 pos2 = _col2->transform->GetWorldPosition();
	size = _col2->transform->GetWorldScale();
	Vector3 size2 = _col2->size;
	size2.x *= size.x / 2;
	size2.y *= size.y / 2;
	size2.z *= size.z / 2;

	Vector3 col1min = pos1 - size1;
	Vector3 col1max = pos1 + size1;
	Vector3 col2min = pos2 - size2;
	Vector3 col2max = pos2 + size2;

	if (col1max.x < col2min.x || col1min.x > col2max.x)
		return false;
	if (col1max.y < col2min.y || col1min.y > col2max.y)
		return false;
	if (col1max.z < col2min.z || col1min.z > col2max.z)
		return false;

	return true;
}

bool Collider::CollisionCheckBtoS(BoxCollider* _col1, SphereCollider* _col2)
{
	if (!_col1->gameObject->isActive() || !_col2->gameObject->isActive()) return false;

	Vector3 pos1 = _col1->transform->GetWorldPosition();
	Vector3 size = _col1->transform->GetWorldScale();
	Vector3 size1 = _col1->size;
	size1.x *= size.x / 2;
	size1.y *= size.y / 2;
	size1.z *= size.z / 2;

	Vector3 col1min = pos1 - size1;
	Vector3 col1max = pos1 + size1;

	Vector3 pos2 = _col2->transform->GetWorldPosition();
	Vector3 scale = _col2->transform->GetWorldScale();
	float rate = (scale.x + scale.y + scale.z) / 3.f;
	float length = rate * _col2->radius;

	Vector3 closepoint;

	if (pos2.x < pos1.x - size1.x) closepoint.x = pos1.x - size1.x;
	else if (pos2.x > pos1.x + size1.x)	closepoint.x = pos1.x + size1.x;
	else closepoint.x = pos2.x;

	if (pos2.y < pos1.y - size1.y) closepoint.y = pos1.y - size1.y;
	else if (pos2.y > pos1.y + size1.y)	closepoint.y = pos1.y + size1.y;
	else closepoint.y = pos2.y;

	if (pos2.z < pos1.z - size1.z) closepoint.z = pos1.z - size1.z;
	else if (pos2.z > pos1.z + size1.z)	closepoint.z = pos1.z + size1.z;
	else closepoint.z = pos2.z;

	return Functions::GetDistance(pos2, closepoint) < length;
}

bool Collider::CollisionCheckStoS(SphereCollider* _col1, SphereCollider* _col2)
{
	if (!_col1->gameObject->isActive() || !_col2->gameObject->isActive()) return false;

	float distance = Functions::GetDistance(_col1->transform->GetWorldPosition(), _col2->transform->GetWorldPosition());

	Vector3 scale = _col1->transform->GetWorldScale();
	float rate1 = (scale.x + scale.y + scale.z) / 3.f;
	scale = _col2->transform->GetWorldScale();
	float rate2 = (scale.x + scale.y + scale.z) / 3.f;
	float limitlength = _col1->radius * rate1 + _col2->radius * rate2;

	return limitlength > distance;
}