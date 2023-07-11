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

vector<GameObject*> GameObject::safedestroy;

bool GameObject::TransformCheck(const string& _key)
{
	if (typeid(Transform).name() == _key || typeid(RectTransform).name() == _key)
	{
		Transform* transform = GetComponentFromObject(this, Transform);
		RectTransform* recttransform = GetComponentFromObject(this, RectTransform);

		if (transform != nullptr || recttransform != nullptr)
		{
			return false;
		}
	}
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

	while (components.size() > 0)
	{
		components[0] = nullptr;
		components.erase(components.begin());
	}

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

bool GameObject::isStarted()
{
	if (started) return true;
	else return false;
}

bool GameObject::isActive()
{
	if (active) return true;
	else return false;
}

void GameObject::Start()
{
	for (int i = 0; i < components.size(); ++i)
	{
		components[i]->Start();
	}
	started = true;
}

void GameObject::Update()
{
	if (!active) return;

	for (int i = 0; i < components.size(); ++i)
	{
		components[i]->Update();
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

void GameObject::Render()
{
	if (!active) return;

	Transform* transform = GetComponentFromObject(this, Transform);
	RectTransform* recttransform = GetComponentFromObject(this, RectTransform);

	if (transform != nullptr)
	{
		MeshRenderer* mesh = GetComponentFromObject(this, MeshRenderer);
		if (mesh != nullptr) mesh->Render();
		VerticeRenderer* vertice = GetComponentFromObject(this, VerticeRenderer);
		if (vertice != nullptr) vertice->Render();

		for (int i = 0; i < transform->GetChildCount(); ++i)
		{
			transform->GetChild(i)->gameObject->Render();
		}
	}

	else if (recttransform != nullptr)
	{
		TextRenderer* text = GetComponentFromObject(this, TextRenderer);
		if (text != nullptr) text->Render();
		SpriteRenderer* sprite = GetComponentFromObject(this, SpriteRenderer);
		if (sprite != nullptr) sprite->Render();

		for (int i = 0; i < recttransform->GetChildCount(); ++i)
		{
			recttransform->GetChild(i)->gameObject->Render();
		}
	}
}

void GameObject::SetActive(bool _active)
{
	if (active == _active) return;

	active = _active;

	if (active)
	{
		for (int i = 0; i < components.size(); ++i)
		{
			components[i]->OnEnabled();
		}
	}
	else
	{
		for (int i = 0; i < components.size(); ++i)
		{
			components[i]->OnDisabled();
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
	for (int i = 0; i < components.size(); ++i)
	{
		if (components[i] == _ptr)
		{
			components[i] = nullptr;
			components.erase(components.begin() + i);

			for (pair<string, Component*> pair : componentsmap)
			{
				if (pair.second == _ptr)
				{
					componentsmap.erase(pair.first);
					break;
				}
			}
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

	for (int i = 0; i < g_Objects.size(); ++i)
	{
		if (g_Objects[i]() == nullptr)
		{
			g_Objects.erase(g_Objects.begin() + i--);
		}
	}

	safedestroy.clear();
}

void GameObject::Erase(GameObject* _gameObject)
{
	for (int i = 0; i < g_Objects.size(); ++i)
	{
		if (g_Objects[i] == _gameObject)
		{
			g_Objects[i] = nullptr;
			break;
		}
	}
}

bool GameObject::Exists(GameObject* _gameObject)
{
	for (int i = 0; i < g_Objects.size(); ++i)
	{
		if (g_Objects[i] == _gameObject) return true;
	}
	return false;
}

void GameObject::operator = (void* _ptr)
{
	if (_ptr == nullptr) GameObject::Destroy(this);
}