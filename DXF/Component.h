//-----------------------------------------------------------------------------
// File: Component
//
// Desc: GameObject에 추가할 수 있는 Component의 기본형
//		 Component(Script)를 추가한 후 이 클래스를 상속한 후 아래의 함수들을
//		 Override하여 구현할 경우 아래의 기능이 수행됨
//
//		[Variables]
//		- gameObject: 해당 컴포넌트의 소유 오브젝트 (AddComponent 시 자동 추가됨)
//
//		[Functions]
//      - Start: Active 상태인 오브젝트의 최초의 Update()가 실행되기 전에 1회 실행
//				 (오브젝트가 생성된 순서대로 실행)
//      - Update: 매 프레임마다 실행 (Transform의 Parent/Child 구조 순으로 실행)
//
//      [MouseFunction 컴포넌트를 소유하고 있어야 작동]
//		[Transform 오브젝트의 경우 Collider 컴포넌트를 소유하고 있어야 작동]
//		- OnMouseEnter: 해당 오브젝트에 처음 마우스가 오버될 때 실행 
//		- OnMouseExit: 해당 오브젝트에 마우스 오버가 해제될 때 실행
//		- OnMouseOver: 해당 오브젝트에 마우스 오버중일 때 매 프레임마다 실행
//		- OnMouseDown: 해당 오브젝트를 클릭했을 때 실행
//		- OnMouseUp: 해당 오브젝트의 클릭이 해제됐을 때 실행
//		- OnMouseHold: 해당 오브젝트를 클릭중일 때 매 프레임마다 실행
//
//		[충돌을 감시할 두 오브젝트 모두 Collider 컴포넌트를 소유하고 있어야 작동]
//      - OnTriggerEnter: 두 오브젝트가 처음 충돌할 때 실행
//      - OnTriggerExit: 두 오브젝트의 충돌 상태가 해제될 때 실행
//      - OnTriggerStay: 두 오브젝트가 충돌중일 때 매 프레임마다 실행
//
//      - OnEnabled: 오브젝트의 Active 상태가 true로 변할 때 실행
//      - OnDisabled: 오브젝트의 Active 상태가 false로 변할 때 실행
//      - OnDestroy: 오브젝트가 소멸되기 직전에 실행
//-----------------------------------------------------------------------------

#pragma once
#include "GameObject.h"

class Collider;

class Component
{
protected:

public:
	GameObject* gameObject = nullptr;
	virtual ~Component() { OnDestroy(); }

	virtual void Start() {};
	virtual void Update() {};

	virtual void OnMouseEnter() {};
	virtual void OnMouseExit() {};
	virtual void OnMouseOver() {};
	virtual void OnMouseDown() {};
	virtual void OnMouseUp() {};
	virtual void OnMouseHold() {};

	virtual void OnTriggerEnter(Collider* p_Collider) {};
	virtual void OnTriggerExit(Collider* p_Collider) {};
	virtual void OnTriggerStay(Collider* p_Collider) {};

	virtual void OnEnabled() {};
	virtual void OnDisabled() {};
	virtual void OnDestroy() {};
};