//-----------------------------------------------------------------------------
// File: PlayerMove
//
// Desc: �÷��̾� ������Ʈ�� �̵��� ���� ��ũ��Ʈ
//
//		[Variables]
//		- m_Transform: ������Ʈ�� Transform ������Ʈ
//		- m_Speed: �̵� �ӷ�
//
//		- player: Ÿ ��ũ��Ʈ���� ������ ���� ���
//		- m_Triggered: �浹 ���� ����
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"

class GameObject;
class Transform;
class Collider;

class PlayerMove : public Component
{
protected:
	Transform*			m_Transform;
	float				m_Speed;

public:
	static PlayerMove*	player;
	bool				m_isTriggered = false;

public:
	PlayerMove(float p_Speed);

	void Start() override;
	void Update() override;
	void OnMouseDown() override;
	void OnTriggerStay(Collider* p_Collider) override;
	void OnTriggerExit(Collider* p_Collider) override;

	SerializeFunction(PlayerMove)
	{
		Serialize(m_Speed);
	}
	DeserializeFunction()
	{
		Deserialize(m_Speed);
	}
};

