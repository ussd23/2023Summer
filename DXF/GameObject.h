//-----------------------------------------------------------------------------
// File: GameObject
//
// Desc: 게임 오브젝트 클래스
//
//		[Variables]
//		- started: 최초의 Start가 실행되었는 지 여부
//		- active: Update와 Render를 실행할 지 여부
//		- name: 해당 오브젝트의 이름 (string 기반 오브젝트 검색 등에 사용)
//		- componentsmap: string 기반의 컴포넌트 목록
//		- safedestroy: 삭제 대기 오브젝트 목록 (모든 Update와 Render가 완료된
//					   후에 안전하게 삭제되도록 함)
//		- components: 컴포넌트 목록 (타 클래스에서 접근하여 컴포넌트의 특정 함수를
//					  실행할 수 있도록 함)
//
//		[Functions]
//		- TransformCheck: Transform과 RectTransform이 동시에 존재하지 않도록 제한
//		- Erase: 오브젝트 삭제
// 
//		- AddComponent: 이미지 파일을 기반으로 텍스쳐 인터페이스를 검색하여 반환
//		- GetComponent: 텍스쳐 인터페이스 삭제
//
//		- isStarted: started 반환
//		- isActive: active 반환
//		- SetActive: active 상태 설정 및 모든 컴포넌트의 OnEnable, OnDisable 실행
//		- ObjectInit: 컴포넌트의 gameObject를 자신으로 설정
//
//		- Start: 모든 컴포넌트의 Start 일괄 실행
//		- Update: 모든 컴포넌트의 Update 일괄 실행 후 Child의 Update 실행
//		- Render: Render 관련 컴포넌트의 Render 일괄 실행 후 Child의 Render 실행
//
//		- Destroy: 해당 오브젝트를 삭제 대기열에 올림
//		- SafeDestroy: 모든 Update와 Render가 완료된 이후에 삭제 대기열에 있는
//					   오브젝트 삭제
//		- Exists: 해당 오브젝트가 삭제되었는 지의 여부 반환 (타 오브젝트 호출 시
//				  사용하여 예외 처리 권장, GetComponentFromObject에서는 자동 적용)
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