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
#include "BoxCollider2D.h"
#include "SphereCollider2D.h"

#define AddObjectToScene(object, parent) { Var::Objects.push_back(object);\
        Transform* obj = GetComponentFromObject(object, Transform);\
        Transform* par = GetComponentFromObject(parent, Transform);\
        if (par != nullptr && obj != nullptr) par->AddChild(obj);\
        else { RectTransform* robj = GetComponentFromObject(object, RectTransform);\
        RectTransform* rpar = GetComponentFromObject(parent, RectTransform);\
        if (rpar != nullptr && robj != nullptr) rpar->AddChild(robj); } }

map<GameObject*, float> GameObject::m_SafeDestroy;

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
	Transform* transform = GetComponentFromObject(this, Transform);
	RectTransform* recttransform = GetComponentFromObject(this, RectTransform);

	if (transform != nullptr)
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

		Var::ColliderObjects.push_back(this);
	}

	else if (recttransform != nullptr)
	{
		BoxCollider2D* bcollider = dynamic_cast<BoxCollider2D*>(p_Comp);
		SphereCollider2D* scollider = dynamic_cast<SphereCollider2D*>(p_Comp);

		if (bcollider == nullptr && scollider == nullptr) return true;

		map<string, Component*>::iterator iter = m_ComponentsMap.find(typeid(BoxCollider2D).name());
		if (iter != m_ComponentsMap.end())
		{
			return false;
		}

		iter = m_ComponentsMap.find(typeid(SphereCollider2D).name());
		if (iter != m_ComponentsMap.end())
		{
			return false;
		}

		Var::Collider2DObjects.push_back(this);
	}

	return true;
}

GameObject::GameObject(const string& p_Name)
	: m_Name(p_Name) {}

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

	if (Var::RootObject == this) Var::RootObject = nullptr;
	else if (Var::RootRectObject == this) Var::RootRectObject = nullptr;
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

Component* GameObject::GetComponent(int p_Index)
{
	list<SPTR<Component>>::iterator iter = m_Components.begin();

	for (int i = 0; iter != m_Components.end(); ++i, ++iter)
	{
		if (i == p_Index) return (*iter)();
	}

	return nullptr;
}

void GameObject::RemoveComponent(Component* p_Comp)
{
	list<SPTR<Component>>::iterator iter = m_Components.begin();

	string id = typeid(*p_Comp).name();
	if (typeid(Transform).name() == id || typeid(RectTransform).name() == id) return;

	while (iter != m_Components.end())
	{
		if (p_Comp == (*iter)())
		{
			m_Components.erase(iter);
			break;
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

bool GameObject::isActive()
{
	if (m_isActive) return true;
	else return false;
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
	Var::NewComponents.push_back(p_Comp);
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
		int count = transform->GetChildCount();
		for (int i = 0; i < count; ++i)
		{
			transform->GetChild(i)->gameObject->PreUpdate();
		}
	}

	else if (recttransform != nullptr)
	{
		int count = recttransform->GetChildCount();
		for (int i = 0; i < count; ++i)
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
		int count = transform->GetChildCount();
		for (int i = 0; i < count; ++i)
		{
			transform->GetChild(i)->gameObject->Update();
		}
	}

	else if (recttransform != nullptr)
	{
		int count = recttransform->GetChildCount();
		for (int i = 0; i < count; ++i)
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
		int count = transform->GetChildCount();
		for (int i = 0; i < count; ++i)
		{
			transform->GetChild(i)->gameObject->LateUpdate();
		}
	}

	else if (recttransform != nullptr)
	{
		int count = recttransform->GetChildCount();
		for (int i = 0; i < count; ++i)
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

		int count = transform->GetChildCount();
		for (int i = 0; i < count; ++i)
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

		int count = recttransform->GetChildCount();
		for (int i = 0; i < count; ++i)
		{
			recttransform->GetChild(i)->gameObject->PreRender();
		}
	}
}

void GameObject::DebugInsert(HWND p_hWnd, HTREEITEM p_hTItem)
{
	TVINSERTSTRUCT ti;
	ZeroMemory(&ti, sizeof(TVINSERTSTRUCT));
	ti.hParent = p_hTItem;
	ti.hInsertAfter = TVI_LAST;
	ti.item.mask = TVIF_TEXT | TVIF_PARAM;
	string itemname = "¡¤ " + m_Name;
	ti.item.pszText = const_cast<char*>(itemname.c_str());

	Transform* transform = GetComponentFromObject(this, Transform);
	RectTransform* recttransform = GetComponentFromObject(this, RectTransform);

	HTREEITEM item = TVI_ROOT;

	if (transform != nullptr)
	{
		if (DXFGame::m_HTab == 2)
		{
			item = TreeView_InsertItem(p_hWnd, &ti);
		}
		else
		{
			if (transform != Var::RootTransform)
			{
				if (transform->GetParent() == Var::RootTransform)
				{
					ti.hParent = TVI_ROOT;
				}
				item = TreeView_InsertItem(p_hWnd, &ti);
			}
		}

		int count = transform->GetChildCount();
		for (int i = 0; i < count; ++i)
		{
			transform->GetChild(i)->gameObject->DebugInsert(p_hWnd, item);
		}
	}

	else if (recttransform != nullptr)
	{
		if (DXFGame::m_HTab == 2)
		{
			item = TreeView_InsertItem(p_hWnd, &ti);
		}
		else
		{
			if (recttransform != Var::RootRectTransform)
			{
				if (recttransform->GetParent() == Var::RootRectTransform)
				{
					ti.hParent = TVI_ROOT;
				}
				item = TreeView_InsertItem(p_hWnd, &ti);
			}
		}

		int count = recttransform->GetChildCount();
		for (int i = 0; i < count; ++i)
		{
			recttransform->GetChild(i)->gameObject->DebugInsert(p_hWnd, item);
		}
	}

	if (m_DebugExtended)
	{
		TreeView_Expand(p_hWnd, item, TVM_EXPAND);
	}

	if (this == Var::DebugSelected) Var::DebugHandle = item;
	Var::DebugObjectMap.insert(make_pair(item, this));
}

void GameObject::Destroy(GameObject* p_GameObject)
{
	m_SafeDestroy.insert(make_pair(p_GameObject, 0.f));
}

void GameObject::Destroy(GameObject* p_GameObject, float p_Time)
{
	m_SafeDestroy.insert(make_pair(p_GameObject, p_Time));
}

void GameObject::SafeDestroy()
{
	if (Time::paused) return;
	if (m_SafeDestroy.size() == 0) return;

	map<GameObject*, float>::iterator iter = m_SafeDestroy.begin();

	while (iter != m_SafeDestroy.end())
	{
		iter->second -= Time::deltaTime;

		if (iter->second <= 0.f)
		{
			Erase(iter->first);
			iter = m_SafeDestroy.erase(iter);

			continue;
		}

		++iter;
	}
}

void GameObject::Erase(GameObject* p_GameObject)
{
	if (DXFGame::m_DebugMode) DXFGame::DebugUpdate();

	list<SPTR<GameObject>>::iterator iter = Var::Objects.begin();

	while (iter != Var::Objects.end())
	{
		if (p_GameObject == (*iter)())
		{
			*iter = nullptr;
			Var::Objects.erase(iter);
			return;
		}
		++iter;
	}

	list<GameObject*>::iterator iter2 = Var::ColliderObjects.begin();

	while (iter2 != Var::ColliderObjects.end())
	{
		if (p_GameObject == *iter2)
		{
			Var::ColliderObjects.erase(iter2);
			return;
		}
		++iter2;
	}

	iter2 = Var::Collider2DObjects.begin();

	while (iter2 != Var::Collider2DObjects.end())
	{
		if (p_GameObject == *iter2)
		{
			Var::Collider2DObjects.erase(iter2);
			return;
		}
		++iter2;
	}
}

bool GameObject::Exists(GameObject* p_GameObject)
{
	list<SPTR<GameObject>>::iterator iter = Var::Objects.begin();

	while (iter != Var::Objects.end())
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
	list<SPTR<GameObject>>::iterator iter = Var::Objects.begin();

	while (iter != Var::Objects.end())
	{
		if ((*iter)->m_Name == p_Name)
		{
			return (*iter)();
		}
		++iter;
	}
	return nullptr;
}

int GameObject::ObjectID(Transform* p_Transform)
{
	list<SPTR<GameObject>>::iterator iter = Var::Objects.begin();

	int index = -1;
	while (iter != Var::Objects.end())
	{
		++index;
		if ((*iter) == p_Transform->gameObject)
		{
			return index;
		}
		++iter;
	}
	return index;
}

int GameObject::ObjectID(RectTransform* p_RectTransform)
{
	list<SPTR<GameObject>>::iterator iter = Var::Objects.begin();

	int index = -1;
	while (iter != Var::Objects.end())
	{
		++index;
		if ((*iter) == p_RectTransform->gameObject)
		{
			return index;
		}
		++iter;
	}
	return index;
}

GameObject* GameObject::Instantiate(GameObject* p_GameObject)
{
	Json::Value value;
	p_GameObject->JsonSerialize(value);
	
	GameObject* newObject = new GameObject;
	newObject->JsonDeserialize(value);

	GameObject* parent = nullptr;

	Transform* transform = GetComponentFromObject(p_GameObject, Transform);
	if (transform != nullptr)
	{
		parent = transform->GetParent()->gameObject;
	}
	RectTransform* recttransform = GetComponentFromObject(p_GameObject, RectTransform);
	if (recttransform != nullptr)
	{
		parent = recttransform->GetParent()->gameObject;
	}

	if (parent != nullptr)
	{
		AddObjectToScene(newObject, parent);

		if (transform != nullptr)
		{
			Transform* newTransform = GetComponentFromObject(newObject, Transform);

			for (int i = 0; i < transform->GetChildCount(); ++i)
			{
				GameObject* child = transform->GetChild(i)->gameObject;
				GameObject* newChild = Instantiate(child);
				Transform* childTransform = GetComponentFromObject(newChild, Transform);
				
				newTransform->AddChild(childTransform);
			}
		}
		if (recttransform != nullptr)
		{
			RectTransform* newRecttransform = GetComponentFromObject(newObject, RectTransform);

			for (int i = 0; i < recttransform->GetChildCount(); ++i)
			{
				GameObject* child = recttransform->GetChild(i)->gameObject;
				GameObject* newChild = Instantiate(child);
				RectTransform* childRecttransform = GetComponentFromObject(newChild, RectTransform);

				newRecttransform->AddChild(childRecttransform);
			}
		}
	}
	else
	{
		delete newObject;
		newObject = nullptr;
	}

	return newObject;
}

void GameObject::operator = (void* p_Ptr)
{
	if (p_Ptr == nullptr) GameObject::Destroy(this);
}

void GameObject::JsonFunction(Json::Value& p_JsonValue, const bool& p_Mode)
{
	Serialize(m_Name);
	Serialize(m_isActive);
	if (p_Mode)
	{
		vector<Component*> components;
		for (SPTR<Component> c : m_Components) components.push_back(c());
		ComponentSerialize(components);
	}
	else
	{
		vector<Component*> components;
		ComponentSerialize(components);
		for (Component* c : components) AddComponent(c);
	}
}