//-----------------------------------------------------------------------------
// File: GameObject
//
// Desc: ���� ������Ʈ Ŭ����
//
//		[Variables]
//		- active: Update�� Render�� ������ �� ����
//		- name: �ش� ������Ʈ�� �̸� (string ��� ������Ʈ �˻� � ���)
//		- componentsmap: string ����� ������Ʈ ���
//		- safedestroy: ���� ��� ������Ʈ ��� (��� Update�� Render�� �Ϸ��
//					   �Ŀ� �����ϰ� �����ǵ��� ��)
//		- components: ������Ʈ ��� (Ÿ Ŭ�������� �����Ͽ� ������Ʈ�� Ư�� �Լ���
//					  ������ �� �ֵ��� ��)
//
//		[Functions]
//		- TransformCheck: Transform�� RectTransform�� ���ÿ� �������� �ʵ��� ����
//		- Erase: ������Ʈ ����
// 
//		- AddComponent: �̹��� ������ ������� �ؽ��� �������̽��� �˻��Ͽ� ��ȯ
//		- GetComponent: �ؽ��� �������̽� ����
//
//		- isActive: active ��ȯ
//		- SetActive: active ���� ���� �� ��� ������Ʈ�� OnEnable, OnDisable ����
//		- ObjectInit: ������Ʈ�� gameObject�� �ڽ����� ����
//
//		- Start: ��� ������Ʈ�� Start �ϰ� ����
//		- Update: ��� ������Ʈ�� Update �ϰ� ���� �� Child�� Update ����
//		- Render: Render ���� ������Ʈ�� Render �ϰ� ���� �� Child�� Render ����
//
//		- Destroy: �ش� ������Ʈ�� ���� ��⿭�� �ø�
//		- SafeDestroy: ��� Update�� Render�� �Ϸ�� ���Ŀ� ���� ��⿭�� �ִ�
//					   ������Ʈ ����
//		- Exists: �ش� ������Ʈ�� �����Ǿ��� ���� ���� ��ȯ (Ÿ ������Ʈ ȣ�� ��
//				  ����Ͽ� ���� ó�� ����, GetComponentFromObject������ �ڵ� ����)
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
	bool							active = true;
	map<string, Component*>			componentsmap;
	static vector<GameObject*>		safedestroy;

public:
	string							name;
	list<SPTR<Component>>			components;

private:
	bool TransformCheck(const string&);
	static void Erase(GameObject*);

public:
	GameObject(string);
	virtual ~GameObject();

	template <class T> void AddComponent(T* _comp);
	Component* GetComponent(const string&);
	template <class T> T* GetComponent();
	void RemoveComponent(Component*);

	bool isActive();
	void SetActive(bool);
	void ObjectInit(Component*);

	void Update();
	void Render();

	static void Destroy(GameObject*);
	static void SafeDestroy();
	static bool Exists(GameObject*);

	void operator = (void*);
};

template <class T> void GameObject::AddComponent(T* _comp)
{
	string key = typeid(T).name();

	Component* comp = dynamic_cast<Component*>(_comp);
	if (comp)
	{
		if (!TransformCheck(key))
		{
			delete _comp;
			return;
		}

		map<string, Component*>::iterator iter = componentsmap.find(key);
		if (iter != componentsmap.end())
		{
			delete _comp;
			return;
		}

		ObjectInit(comp);

		components.push_back(comp);
		componentsmap.insert(make_pair(key, comp));
	}
}

template <class T> T* GameObject::GetComponent()
{
	string key = typeid(T).name();

	map<string, Component*>::iterator iter = componentsmap.find(key);
	if (iter != componentsmap.end())
	{
		return nullptr;
	}

	return componentsmap[key];
}