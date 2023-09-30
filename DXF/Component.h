//-----------------------------------------------------------------------------
// File: Component
//
// Desc: GameObject�� �߰��� �� �ִ� Component�� �⺻��
//		 Component(Script)�� �߰��� �� �� Ŭ������ ����� �� �Ʒ��� �Լ�����
//		 Override�Ͽ� ������ ��� �Ʒ��� ����� �����
//
//		[Variables]
//		- gameObject: �ش� ������Ʈ�� ���� ������Ʈ (AddComponent �� �ڵ� �߰���)
//
//		[Functions]
//      - Start: Active ������ ������Ʈ�� ������ Update()�� ����Ǳ� ���� 1ȸ ����
//				 (������Ʈ�� ������ ������� ����)
//      - PreUpdate: Update ������ ����
//      - Update: �� �����Ӹ��� ���� (Transform�� Parent/Child ���� ������ ����)
//      - LateUpdate: Update ���Ŀ� ����
//
//      [MouseFunction ������Ʈ�� �����ϰ� �־�� �۵�]
//		[Transform ������Ʈ�� ��� Collider ������Ʈ�� �����ϰ� �־�� �۵�]
//		- OnMouseEnter: �ش� ������Ʈ�� ó�� ���콺�� ������ �� ���� 
//		- OnMouseExit: �ش� ������Ʈ�� ���콺 ������ ������ �� ����
//		- OnMouseOver: �ش� ������Ʈ�� ���콺 �������� �� �� �����Ӹ��� ����
//		- OnMouseDown: �ش� ������Ʈ�� Ŭ������ �� ����
//		- OnMouseUp: �ش� ������Ʈ�� Ŭ���� �������� �� ����
//		- OnMouseHold: �ش� ������Ʈ�� Ŭ������ �� �� �����Ӹ��� ����
//
//		[�浹�� ������ �� ������Ʈ ��� Collider ������Ʈ�� �����ϰ� �־�� �۵�]
//      - OnTriggerEnter: �� ������Ʈ�� ó�� �浹�� �� ����
//      - OnTriggerExit: �� ������Ʈ�� �浹 ���°� ������ �� ����
//      - OnTriggerStay: �� ������Ʈ�� �浹���� �� �� �����Ӹ��� ����
//
//      - OnEnabled: ������Ʈ�� Active ���°� true�� ���� �� ����
//      - OnDisabled: ������Ʈ�� Active ���°� false�� ���� �� ����
//      - OnDestroy: ������Ʈ�� �Ҹ�Ǳ� ������ ����
//-----------------------------------------------------------------------------

#pragma once
#include "GameObject.h"

class Collider;

class Component : public Serializable
{
protected:

public:
	GameObject* gameObject = nullptr;
	virtual ~Component() { OnDestroy(); }

	virtual void Awake() {};
	virtual void Start() {};
	virtual void PreUpdate() {};
	virtual void Update() {};
	virtual void LateUpdate() {};

	virtual void OnMouseEnter() {};
	virtual void OnMouseExit() {};
	virtual void OnMouseOver() {};
	virtual void OnMouseDown() {};
	virtual void OnMouseUp() {};
	virtual void OnMouseHold() {};
	virtual void OnWheelDown() {};
	virtual void OnWheelUp() {};

	virtual void OnTriggerEnter(Collider* p_Collider) {};
	virtual void OnTriggerExit(Collider* p_Collider) {};
	virtual void OnTriggerStay(Collider* p_Collider) {};

	virtual void OnEditorUpdate() {};
	virtual void OnEnabled() {};
	virtual void OnDisabled() {};
	virtual void OnDestroy() {};
};