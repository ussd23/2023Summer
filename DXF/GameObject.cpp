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

vector<GameObject*> GameObject::m_SafeDestroy;

bool GameObject::TransformCheck(const string& p_Key)
{
	if (typeid(Transform).name() == p_Key || typeid(RectTransform).name() == p_Key)
	{
		map<string, Component*>::iterator iter = m_ComponentsMap.find(typeid(Transform).name());
		if (iter != m_ComponentsMap.end())
		{
			return false;
		}

		iter = m_ComponentsMap.find(typeid(RectTransform).name());
		if (iter != m_ComponentsMap.end())
		{
			return false;
		}
	}
	return true;
}

bool GameObject::ColliderCheck(Component* p_Comp)
{
	BoxCollider* bcollider = dynamic_cast<BoxCollider*>(p_Comp);
	SphereCollider* scollider = dynamic_cast<SphereCollider*>(p_Comp);

	if (bcollider == nullptr && scollider == nullptr) return true;

	map<string, Component*>::iterator iter = m_ComponentsMap.find(typeid(BoxCollider).name());
	if (iter != m_ComponentsMap.end())
	{
		return false;
	}

	iter = m_ComponentsMap.find(typeid(SphereCollider).name());
	if (iter != m_ComponentsMap.end())
	{
		return false;
	}

	g_ColliderObjects.push_back(this);

	return true;
}

GameObject::GameObject(const string& p_Name)
{
	m_Name = p_Name;
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

	m_Components.clear();

	for (int i = 0; i < m_SafeDestroy.size(); ++i)
	{
		if (m_SafeDestroy[i] == this)
		{
			m_SafeDestroy[i] = nullptr;
			break;
		}
	}

	if (g_RootObject == this) g_RootObject = nullptr;
	else if (g_RootRectObject == this) g_RootRectObject = nullptr;
}

bool GameObject::isActive()
{
	if (m_isActive) return true;
	else return false;
}

void GameObject::PreUpdate()
{
	if (!m_isActive) return;

	list<SPTR<Component>>::iterator iter = m_Components.begin();

	while (iter != m_Components.end())
	{
		(*iter++)->PreUpdate();
	}

	Transform* transform = GetComponentFromObject(this, Transform);
	RectTransform* recttransform = GetComponentFromObject(this, RectTransform);

	if (transform != nullptr)
	{
		for (int i = 0; i < transform->GetChildCount(); ++i)
		{
			transform->GetChild(i)->gameObject->PreUpdate();
		}
	}

	else if (recttransform != nullptr)
	{
		for (int i = 0; i < recttransform->GetChildCount(); ++i)
		{
			recttransform->GetChild(i)->gameObject->PreUpdate();
		}
	}
}

void GameObject::Update()
{
	if (!m_isActive) return;

	list<SPTR<Component>>::iterator iter = m_Components.begin();

	while (iter != m_Components.end())
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

void GameObject::LateUpdate()
{
	if (!m_isActive) return;

	list<SPTR<Component>>::iterator iter = m_Components.begin();

	while (iter != m_Components.end())
	{
		(*iter++)->LateUpdate();
	}

	Transform* transform = GetComponentFromObject(this, Transform);
	RectTransform* recttransform = GetComponentFromObject(this, RectTransform);

	if (transform != nullptr)
	{
		for (int i = 0; i < transform->GetChildCount(); ++i)
		{
			transform->GetChild(i)->gameObject->LateUpdate();
		}
	}

	else if (recttransform != nullptr)
	{
		for (int i = 0; i < recttransform->GetChildCount(); ++i)
		{
			recttransform->GetChild(i)->gameObject->LateUpdate();
		}
	}
}

void GameObject::PreRender()
{
	if (!m_isActive) return;

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

void GameObject::SetActive(bool p_isActive)
{
	if (m_isActive == p_isActive) return;

	m_isActive = p_isActive;

	if (m_isActive)
	{
		list<SPTR<Component>>::iterator iter = m_Components.begin();

		while (iter != m_Components.end())
		{
			(*iter++)->OnEnabled();
		}
	}
	else
	{
		list<SPTR<Component>>::iterator iter = m_Components.begin();

		while (iter != m_Components.end())
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
			transform->GetChild(i)->gameObject->SetActive(m_isActive);
		}
	}
	else if (recttransform != nullptr)
	{
		for (int i = 0; i < recttransform->GetChildCount(); ++i)
		{
			recttransform->GetChild(i)->gameObject->SetActive(m_isActive);
		}
	}
}

void GameObject::ObjectInit(Component* p_Comp)
{
	p_Comp->gameObject = this;
	g_NewComponents.push_back(p_Comp);
}

Component* GameObject::GetComponent(const string& p_Key)
{
	string key = "class " + p_Key;

	map<string, Component*>::iterator iter = m_ComponentsMap.find(key);
	if (iter != m_ComponentsMap.end())
	{
		return iter->second;
	}

	return nullptr;
}

void GameObject::RemoveComponent(Component* p_Comp)
{
	list<SPTR<Component>>::iterator iter = m_Components.begin();

	while (iter != m_Components.end())
	{
		if (p_Comp == (*iter)())
		{
			m_Components.erase(iter);
		}
		++iter;
	}
	
	for (pair<string, Component*> pair : m_ComponentsMap)
	{
		if (pair.second == p_Comp)
		{
			m_ComponentsMap.erase(pair.first);
			break;
		}
	}
}

void GameObject::Destroy(GameObject* p_GameObject)
{
	m_SafeDestroy.push_back(p_GameObject);
}

void GameObject::SafeDestroy()
{
	if (m_SafeDestroy.size() == 0) return;

	while (m_SafeDestroy.size() > 0)
	{
		if (m_SafeDestroy[0] == nullptr) return;

		Erase(m_SafeDestroy[0]);
		m_SafeDestroy.erase(m_SafeDestroy.begin());
	}

	m_SafeDestroy.clear();
}

void GameObject::Erase(GameObject* p_GameObject)
{
	list<SPTR<GameObject>>::iterator iter = g_Objects.begin();

	while (iter != g_Objects.end())
	{
		if (p_GameObject == (*iter)())
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
		if (p_GameObject == *iter2)
		{
			g_ColliderObjects.erase(iter2);
			return;
		}
		++iter2;
	}
}

bool GameObject::Exists(GameObject* p_GameObject)
{
	list<SPTR<GameObject>>::iterator iter = g_Objects.begin();

	while (iter != g_Objects.end())
	{
		if (*iter++ == p_GameObject)
		{
			return true;
		}
	}
	return false;
}

GameObject* GameObject::Search(const string& p_Name)
{
	list<SPTR<GameObject>>::iterator iter = g_Objects.begin();

	while (iter != g_Objects.end())
	{
		if ((*iter)->m_Name == p_Name)
		{
			return (*iter)();
		}
		++iter;
	}
	return nullptr;
}

void GameObject::operator = (void* p_Ptr)
{
	if (p_Ptr == nullptr) GameObject::Destroy(this);
}