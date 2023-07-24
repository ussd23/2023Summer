//-----------------------------------------------------------------------------
// File: GameObject
//
// Desc: ���� ������Ʈ Ŭ����
//
//		[Variables]
//		- m_isActive: Update�� Render�� ������ �� ����
//		- m_ComponentsMap: string ����� ������Ʈ ���
//		- m_SafeDestroy: ���� ��� ������Ʈ ��� (��� Update�� Render�� �Ϸ��
//					   �Ŀ� �����ϰ� �����ǵ��� ��)
//		- m_Name: �ش� ������Ʈ�� �̸� (string ��� ������Ʈ �˻� � ���)
//		- m_Components: ������Ʈ ��� (Ÿ Ŭ�������� �����Ͽ� ������Ʈ�� Ư�� �Լ���
//					  ������ �� �ֵ��� ��)
//
//		[Functions]
//		- TransformCheck: Transform�� RectTransform�� ���ÿ� �������� �ʵ��� ����
//		- ColliderCheck: Collider�� ���õ� ���� Ȯ��
//		- Erase: ������Ʈ ����
// 
//		- AddComponent: �̹��� ������ ������� �ؽ��� �������̽��� �˻��Ͽ� ��ȯ
//		- GetComponent: �ؽ��� �������̽� ����
//
//		- isActive: active ��ȯ
//		- SetActive: active ���� ���� �� ��� ������Ʈ�� OnEnable, OnDisable ����
//		- ObjectInit: ������Ʈ�� gameObject�� �ڽ����� ����
//
//		- PreUpdate: Update ������ ����
//		- Update: ��� ������Ʈ�� Update �ϰ� ���� �� Child�� Update ����
//		- LateUpdate: Update ���Ŀ� ����
//		- PreRender: Render ���� ������Ʈ�� Render �ϰ� ����
//
//		- Destroy: �ش� ������Ʈ�� ���� ��⿭�� �ø�
//		- SafeDestroy: ��� Update�� Render�� �Ϸ�� ���Ŀ� ���� ��⿭�� �ִ�
//					   ������Ʈ ����
//		- Exists: �ش� ������Ʈ�� �����Ǿ��� ���� ���� ��ȯ (Ÿ ������Ʈ ȣ�� ��
//				  ����Ͽ� ���� ó�� ����, GetComponentFromObject������ �ڵ� ����)
//		- Search: name���� ������Ʈ �˻�
//-----------------------------------------------------------------------------

#pragma once
#include "StandardLibrary.h"

class Component;
class Transform;
class RectTransform;
class MeshRenderer;
class VerticeRenderer;
class TextRenderer;
template<typename T> class SPTR;

class GameObject
{
protected:
	bool							m_isActive = true;
	map<string, Component*>			m_ComponentsMap;
	static vector<GameObject*>		m_SafeDestroy;

public:
	string							m_Name;
	list<SPTR<Component>>			m_Components;

protected:
	bool TransformCheck(const string& p_Key);
	bool ColliderCheck(Component* p_Comp);
	static void Erase(GameObject* p_Object);

public:
	GameObject(const string& p_Name);
	virtual ~GameObject();

	template <class T> void AddComponent(T* p_Comp);
	Component* GetComponent(const string& p_Key);
	template <class T> T* GetComponent();
	void RemoveComponent(Component* p_Comp);

	bool isActive();
	void SetActive(bool p_isActive);
	void ObjectInit(Component* p_Comp);

	void PreUpdate();
	void Update();
	void LateUpdate();
	void PreRender();

	static void Destroy(GameObject* p_GameObject);
	static void SafeDestroy();
	static bool Exists(GameObject* p_GameObject);
	static GameObject* Search(const string& p_Name);

	void operator = (void* p_Ptr);
};

template <class T> void GameObject::AddComponent(T* p_Comp)
{
	string key = typeid(T).name();

	Component* comp = dynamic_cast<Component*>(p_Comp);
	if (comp)
	{
		if (!TransformCheck(key))
		{
			delete p_Comp;
			return;
		}

		if (!ColliderCheck(comp))
		{
			delete p_Comp;
			return;
		}

		map<string, Component*>::iterator iter = m_ComponentsMap.find(key);
		if (iter != m_ComponentsMap.end())
		{
			delete p_Comp;
			return;
		}

		ObjectInit(comp);

		m_Components.push_back(comp);
		m_ComponentsMap.insert(make_pair(key, comp));
	}
}

template <class T> T* GameObject::GetComponent()
{
	string key = typeid(T).name();

	map<string, Component*>::iterator iter = m_ComponentsMap.find(key);
	if (iter != m_ComponentsMap.end())
	{
		return nullptr;
	}

	return m_ComponentsMap[key];
}