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

GameObject::GameObject(string _name)
{
	name = _name;
}

GameObject::~GameObject()
{
	Transform* transform = GetComponentFromObject(this, Transform);
	if (transform != nullptr)
	{
		for (int i = 0; i < transform->GetChildCount(); ++i)
		{
			delete transform->GetChild(i)->gameObject;
		}
		if (transform->GetParent() != nullptr)
		{
			transform->GetParent()->RemoveChild(transform);
		}
	}

	RectTransform* recttransform = GetComponentFromObject(this, RectTransform);
	if (recttransform != nullptr)
	{
		for (int i = 0; i < recttransform->GetChildCount(); ++i)
		{
			delete recttransform->GetChild(i)->gameObject;
		}
		if (recttransform->GetParent() != nullptr)
		{
			recttransform->GetParent()->RemoveChild(recttransform);
		}
	}

	for (int i = 0; i < components.size(); ++i)
	{
		delete components[i];
	}

	for (int i = 0; i < g_Objects.size(); ++i)
	{
		if (g_Objects[i] == this)
		{
			g_Objects.erase(g_Objects.begin() + i);
			break;
		}
	}

	for (int i = 0; i < safedestroy.size(); ++i)
	{
		if (safedestroy[i] == this)
		{
			safedestroy[i] = nullptr;
			break;
		}
	}

	if (this == g_RootObject) g_RootObject = nullptr;
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
	if (transform != nullptr)
	{
		for (int i = 0; i < transform->GetChildCount(); ++i)
		{
			transform->GetChild(i)->gameObject->Update();
		}
	}
	RectTransform* recttransform = GetComponentFromObject(this, RectTransform);
	if (recttransform != nullptr)
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

	MeshRenderer* mesh = GetComponentFromObject(this, MeshRenderer);
	if (mesh != nullptr) mesh->Render();
	VerticeRenderer* vertice = GetComponentFromObject(this, VerticeRenderer);
	if (vertice != nullptr) vertice->Render();
	TextRenderer* text = GetComponentFromObject(this, TextRenderer);
	if (text != nullptr) text->Render();
	SpriteRenderer* sprite = GetComponentFromObject(this, SpriteRenderer);
	if (sprite != nullptr) sprite->Render();

	Transform* transform = GetComponentFromObject(this, Transform);
	if (transform != nullptr)
	{
		for (int i = 0; i < transform->GetChildCount(); ++i)
		{
			transform->GetChild(i)->gameObject->Render();
		}
	}
	RectTransform* recttransform = GetComponentFromObject(this, RectTransform);
	if (recttransform != nullptr)
	{
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
	if (transform != nullptr)
	{
		for (int i = 0; i < transform->GetChildCount(); ++i)
		{
			transform->GetChild(i)->gameObject->SetActive(active);
		}
	}
	RectTransform* recttransform = GetComponentFromObject(this, RectTransform);
	if (recttransform != nullptr)
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

Component* GameObject::GetComponent(string _key)
{
	string key = "class " + _key;

	map<string, Component*>::iterator iter = componentsmap.find(key);
	if (iter != componentsmap.end())
	{
		return iter->second;
	}

	return nullptr;
}

void GameObject::Destroy(GameObject* _gameObject)
{
	safedestroy.push_back(_gameObject);
}

void GameObject::SafeDestroy()
{
	if (safedestroy.size() == 0) return;

	for (int i = 0; i < safedestroy.size(); ++i)
	{
		if (safedestroy[i] != nullptr)
		{
			delete safedestroy[i];
			safedestroy[i] = nullptr;
		}
	}

	safedestroy.clear();
}

bool GameObject::Exists(GameObject* _gameObject)
{
	for (int i = 0; i < g_Objects.size(); ++i)
	{
		if (g_Objects[i] == _gameObject) return true;
	}
	return false;
}