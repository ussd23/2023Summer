//-----------------------------------------------------------------------------
// File: GameObject
//
// Desc: ���� ������Ʈ Ŭ����
//
//		[Variables]
//		- started: ������ Start�� ����Ǿ��� �� ����
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
//		- isStarted: started ��ȯ
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

class GameObject
{
protected:
	bool							started = false;
	bool							active = true;
	string							name;
	map<string, Component*>			componentsmap;
	static vector<GameObject*>		safedestroy;

public:
	vector<SPTR<Component>>			components;

private:
	bool TransformCheck(const string&);
	static void Erase(GameObject*);

public:
	GameObject(string);
	virtual ~GameObject();

	template <class T> void AddComponent(T* _comp);
	Component* GetComponent(const string&);

	bool isStarted();
	bool isActive();
	void SetActive(bool);
	void ObjectInit(Component*);

	void Start();
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