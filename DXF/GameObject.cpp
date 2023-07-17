#include "Global.h"
#include "Functions.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "RectTransform.h"
#include "MeshRenderer.h"
#include "TextRenderer.h"
#include "VerticeRenderer.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

vector<GameObject*> GameObject::safedestroy;

bool GameObject::TransformCheck(const string& _key)
{
	if (typeid(Transform).name() == _key || typeid(RectTransform).name() == _key)
	{
		map<string, Component*>::iterator iter = componentsmap.find(typeid(Transform).name());
		if (iter != componentsmap.end())
		{
			return false;
		}

		iter = componentsmap.find(typeid(RectTransform).name());
		if (iter != componentsmap.end())
		{
			return false;
		}
	}
	return true;
}

bool GameObject::ColliderCheck(Component* _comp)
{
	BoxCollider* bcollider = dynamic_cast<BoxCollider*>(_comp);
	SphereCollider* scollider = dynamic_cast<SphereCollider*>(_comp);

	if (bcollider == nullptr && scollider == nullptr) return true;

	map<string, Component*>::iterator iter = componentsmap.find(typeid(BoxCollider).name());
	if (iter != componentsmap.end())
	{
		return false;
	}

	iter = componentsmap.find(typeid(SphereCollider).name());
	if (iter != componentsmap.end())
	{
		return false;
	}

	g_ColliderObjects.push_back(this);

	return true;
}

GameObject::GameObject(string _name)
{
	name = _name;
}

GameObject::~GameObject()
{
	Transform* transform = GetComponentFromObject(this, Transform);
	RectTransform* recttransform = GetComponentFromObject(this, RectTransform);

	if (transform != nullptr)
	{
		while (transform->GetChildCount() > 0)
		{
			Erase(transform->GetChild(0)->gameObject);
		}
		if (transform->GetParent() != nullptr)
		{
			transform->GetParent()->RemoveChild(transform);
		}
	}

	else if (recttransform != nullptr)
	{
		while (recttransform->GetChildCount() > 0)
		{
			Erase(recttransform->GetChild(0)->gameObject);
		}
		if (recttransform->GetParent() != nullptr)
		{
			recttransform->GetParent()->RemoveChild(recttransform);
		}
	}

	components.clear();

	for (int i = 0; i < safedestroy.size(); ++i)
	{
		if (safedestroy[i] == this)
		{
			safedestroy[i] = nullptr;
			break;
		}
	}

	if (g_RootObject == this) g_RootObject = nullptr;
	else if (g_RootRectObject == this) g_RootRectObject = nullptr;
}

bool GameObject::isActive()
{
	if (active) return true;
	else return false;
}

void GameObject::Update()
{
	if (!active) return;

	list<SPTR<Component>>::iterator iter = components.begin();

	while (iter != components.end())
	{
		(*iter++)->Update();
	}

	Transform* transform = GetComponentFromObject(this, Transform);
	RectTransform* recttransform = GetComponentFromObject(this, RectTransform);

	if (transform != nullptr)
	{
		for (int i = 0; i < transform->GetChildCount(); ++i)
		{
			transform->GetChild(i)->gameObject->Update();
		}
	}

	else if (recttransform != nullptr)
	{
		for (int i = 0; i < recttransform->GetChildCount(); ++i)
		{
			recttransform->GetChild(i)->gameObject->Update();
		}
	}
}

void GameObject::PreRender()
{
	if (!active) return;

	Transform* transform = GetComponentFromObject(this, Transform);
	RectTransform* recttransform = GetComponentFromObject(this, RectTransform);

	if (transform != nullptr)
	{
		MeshRenderer* mesh = GetComponentFromObject(this, MeshRenderer);
		if (mesh != nullptr) { mesh->PreRender(); }
		VerticeRenderer* vertice = GetComponentFromObject(this, VerticeRenderer);
		if (vertice != nullptr) { vertice->PreRender(); }

		for (int i = 0; i < transform->GetChildCount(); ++i)
		{
			transform->GetChild(i)->gameObject->PreRender();
		}
	}

	else if (recttransform != nullptr)
	{
		TextRenderer* text = GetComponentFromObject(this, TextRenderer);
		if (text != nullptr) { text->PreRender(); }
		SpriteRenderer* sprite = GetComponentFromObject(this, SpriteRenderer);
		if (sprite != nullptr) { sprite->PreRender(); }

		for (int i = 0; i < recttransform->GetChildCount(); ++i)
		{
			recttransform->GetChild(i)->gameObject->PreRender();
		}
	}
}

void GameObject::SetActive(bool _active)
{
	if (active == _active) return;

	active = _active;

	if (active)
	{
		list<SPTR<Component>>::iterator iter = components.begin();

		while (iter != components.end())
		{
			(*iter++)->OnEnabled();
		}
	}
	else
	{
		list<SPTR<Component>>::iterator iter = components.begin();

		while (iter != components.end())
		{
			(*iter++)->OnDisabled();
		}
	}

	Transform* transform = GetComponentFromObject(this, Transform);
	RectTransform* recttransform = GetComponentFromObject(this, RectTransform);
	if (transform != nullptr)
	{
		for (int i = 0; i < transform->GetChildCount(); ++i)
		{
			transform->GetChild(i)->gameObject->SetActive(active);
		}
	}
	else if (recttransform != nullptr)
	{
		for (int i = 0; i < recttransform->GetChildCount(); ++i)
		{
			recttransform->GetChild(i)->gameObject->SetActive(active);
		}
	}
}

void GameObject::ObjectInit(Component* comp)
{
	comp->gameObject = this;
	g_NewComponents.push_back(comp);
}

Component* GameObject::GetComponent(const string& _key)
{
	string key = "class " + _key;

	map<string, Component*>::iterator iter = componentsmap.find(key);
	if (iter != componentsmap.end())
	{
		return iter->second;
	}

	return nullptr;
}

void GameObject::RemoveComponent(Component* _ptr)
{
	list<SPTR<Component>>::iterator iter = components.begin();

	while (iter != components.end())
	{
		if (_ptr == (*iter)())
		{
			components.erase(iter);
		}
		++iter;
	}
	
	for (pair<string, Component*> pair : componentsmap)
	{
		if (pair.second == _ptr)
		{
			componentsmap.erase(pair.first);
			break;
		}
	}
}

void GameObject::Destroy(GameObject* _gameObject)
{
	safedestroy.push_back(_gameObject);
}

void GameObject::SafeDestroy()
{
	if (safedestroy.size() == 0) return;

	while (safedestroy.size() > 0)
	{
		if (safedestroy[0] == nullptr) return;

		Erase(safedestroy[0]);
		safedestroy.erase(safedestroy.begin());
	}

	safedestroy.clear();
}

void GameObject::Erase(GameObject* _gameObject)
{
	list<SPTR<GameObject>>::iterator iter = g_Objects.begin();

	while (iter != g_Objects.end())
	{
		if (_gameObject == (*iter)())
		{
			*iter = nullptr;
			g_Objects.erase(iter);
			return;
		}
		++iter;
	}

	list<GameObject*>::iterator iter2 = g_ColliderObjects.begin();

	while (iter2 != g_ColliderObjects.end())
	{
		if (_gameObject == *iter2)
		{
			g_ColliderObjects.erase(iter2);
			return;
		}
		++iter2;
	}
}

bool GameObject::Exists(GameObject* _gameObject)
{
	list<SPTR<GameObject>>::iterator iter = g_Objects.begin();

	while (iter != g_Objects.end())
	{
		if (*iter++ == _gameObject)
		{
			return true;
		}
	}
	return false;
}

GameObject* GameObject::Search(const string& _name)
{
	list<SPTR<GameObject>>::iterator iter = g_Objects.begin();

	while (iter != g_Objects.end())
	{
		if ((*iter)->name == _name)
		{
			return (*iter)();
		}
		++iter;
	}
	return nullptr;
}

void GameObject::operator = (void* _ptr)
{
	if (_ptr == nullptr) GameObject::Destroy(this);
}