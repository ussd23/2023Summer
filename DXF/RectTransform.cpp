#include "ComponentHeader.h"

RectTransform::RectTransform(GameObject* _gameObject, Vector2 _pos, Vector3 _rot, Vector2 _scale, Vector2 _size)
{
	gameObject = _gameObject;
	position = _pos;
	rotation = _rot;
	scale = _scale;
	size = _size;
	parent = g_RootRectTransform;
}

Vector2 RectTransform::GetScreenPosition()
{
	if (parent != nullptr)
	{
		Vector2 pscale = parent->GetScreenScale();
		Vector2 pos(pscale.x * position.x, pscale.y * position.y);

		return pos + parent->GetScreenPosition();
	}
	return position;
}

Vector3 RectTransform::GetScreenRotation()
{
	if (parent != nullptr)
	{
		return rotation + parent->GetScreenRotation();
	}
	return rotation;
}

Vector2 RectTransform::GetScreenScale()
{
	if (parent != nullptr)
	{
		Vector2 pscale = parent->GetScreenScale();
		return Vector2(scale.x * pscale.x, scale.y * pscale.y);
	}
	return scale;
}

int RectTransform::GetChildCount()
{
	return childs.size();
}

RectTransform* RectTransform::GetChild(int _index)
{
	return childs[_index];
}

RectTransform* RectTransform::GetParent()
{
	return parent;
}

void RectTransform::AddChild(RectTransform* _child)
{
	_child->parent = this;
	childs.push_back(_child);
}

void RectTransform::AddChildAsFirst(RectTransform* _child)
{
	_child->parent = this;
	childs.insert(childs.begin(), _child);
}

void RectTransform::RemoveChild(RectTransform* _child)
{
	for (int i = 0; i < childs.size(); ++i)
	{
		if (childs[i] == _child)
		{
			_child->parent = nullptr;
			childs.erase(childs.begin() + i);
			break;
		}
	}
}

void RectTransform::SetAsFirstSibling()
{
	parent->RemoveChild(this);
	parent->AddChildAsFirst(this);
}

void RectTransform::SetAsLastSibling()
{
	parent->RemoveChild(this);
	parent->AddChild(this);
}