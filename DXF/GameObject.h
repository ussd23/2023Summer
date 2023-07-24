//-----------------------------------------------------------------------------
// File: GameObject
//
// Desc: 게임 오브젝트 클래스
//
//		[Variables]
//		- m_isActive: Update와 Render를 실행할 지 여부
//		- m_ComponentsMap: string 기반의 컴포넌트 목록
//		- m_SafeDestroy: 삭제 대기 오브젝트 목록 (모든 Update와 Render가 완료된
//					   후에 안전하게 삭제되도록 함)
//		- m_Name: 해당 오브젝트의 이름 (string 기반 오브젝트 검색 등에 사용)
//		- m_Components: 컴포넌트 목록 (타 클래스에서 접근하여 컴포넌트의 특정 함수를
//					  실행할 수 있도록 함)
//
//		[Functions]
//		- TransformCheck: Transform과 RectTransform이 동시에 존재하지 않도록 제한
//		- ColliderCheck: Collider와 관련된 설정 확인
//		- Erase: 오브젝트 삭제
// 
//		- AddComponent: 이미지 파일을 기반으로 텍스쳐 인터페이스를 검색하여 반환
//		- GetComponent: 텍스쳐 인터페이스 삭제
//
//		- isActive: active 반환
//		- SetActive: active 상태 설정 및 모든 컴포넌트의 OnEnable, OnDisable 실행
//		- ObjectInit: 컴포넌트의 gameObject를 자신으로 설정
//
//		- PreUpdate: Update 이전에 실행
//		- Update: 모든 컴포넌트의 Update 일괄 실행 후 Child의 Update 실행
//		- LateUpdate: Update 이후에 실행
//		- PreRender: Render 관련 컴포넌트의 Render 일괄 실행
//
//		- Destroy: 해당 오브젝트를 삭제 대기열에 올림
//		- SafeDestroy: 모든 Update와 Render가 완료된 이후에 삭제 대기열에 있는
//					   오브젝트 삭제
//		- Exists: 해당 오브젝트가 삭제되었는 지의 여부 반환 (타 오브젝트 호출 시
//				  사용하여 예외 처리 권장, GetComponentFromObject에서는 자동 적용)
//		- Search: name으로 오브젝트 검색
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