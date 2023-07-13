//-----------------------------------------------------------------------------
// File: PlayerMove
//
// Desc: �÷��̾� ������Ʈ�� �̵��� ���� ��ũ��Ʈ
//
//		[Variables]
//		- transform: ������Ʈ�� Transform ������Ʈ
//		- movespeed: �̵� �ӷ�
//
//		- player: Ÿ ��ũ��Ʈ���� ������ ���� ���
//		- length: �浹 ���� ����
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"

class GameObject;
class Transform;
class Collider;

class PlayerMove : public Component
{
protected:
	Transform*			transform;
	float				movespeed;

public:
	static PlayerMove*	player;
	bool				triggered = false;

public:
	PlayerMove(float);

	void Start() override;
	void Update() override;
	void OnMouseDown() override;
	void OnTriggerStay(Collider*) override;
	void OnTriggerExit(Collider*) override;
};

