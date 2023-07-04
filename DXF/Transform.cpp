#include "ComponentHeader.h"

Transform::Transform(GameObject* _gameObject, D3DXVECTOR3 _pos, D3DXVECTOR3 _rot, D3DXVECTOR3 _scale)
{
	gameObject = _gameObject;
	position = _pos;
	rotation = _rot;
	scale = _scale;
	parent = g_RootTransform;
}

Transform::~Transform()
{
	for (int i = 0; i < childs.size(); ++i)
	{
		GameObject::Destroy(childs[i]->gameObject);
	}
}

D3DXVECTOR3 Transform::GetWorldPosition()
{
	if (parent != nullptr)
	{
		D3DXVECTOR3 pscale = parent->GetWorldScale();
		D3DXVECTOR3 pos(pscale.x * position.x, pscale.y * position.y, pscale.z * position.z);

		return pos + parent->GetWorldPosition();
	}
	return position;
}

D3DXVECTOR3 Transform::GetWorldRotation()
{
	if (parent != nullptr)
	{
		return rotation + parent->GetWorldRotation();
	}
	return rotation;
}

D3DXVECTOR3 Transform::GetWorldScale()
{
	if (parent != nullptr)
	{
		D3DXVECTOR3 pscale = parent->GetWorldScale();
		return D3DXVECTOR3(scale.x * pscale.x, scale.y * pscale.y, scale.z * pscale.z);
	}
	return scale;
}

int Transform::GetChildCount()
{
	return childs.size();
}

Transform* Transform::GetChild(int _index)
{
	return childs[_index];
}

Transform* Transform::GetParent()
{
	return parent;
}

void Transform::AddChild(Transform* _child)
{
	_child->parent = this;
	childs.push_back(_child);
}

void Transform::AddChildAsFirst(Transform* _child)
{
	_child->parent = this;
	childs.insert(childs.begin(), _child);
}

void Transform::RemoveChild(Transform* _child)
{
	for (int i = 0; i < childs.size(); ++i)
	{
		if (childs[i] == _child)
		{
			_child->parent = g_RootTransform;
			childs.erase(childs.begin() + i);
			break;
		}
	}
}

void Transform::SetAsFirstSibling()
{
	parent->RemoveChild(this);
	parent->AddChildAsFirst(this);
}

void Transform::SetAsLastSibling()
{
	parent->RemoveChild(this);
	parent->AddChild(this);
}