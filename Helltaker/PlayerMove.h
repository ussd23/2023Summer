//-----------------------------------------------------------------------------
// File: PlayerMove
//
// Desc: 플레이어 오브젝트의 이동을 위한 스크립트
//
//		[Variables]
//		- m_Transform: 오브젝트의 Transform 컴포넌트
//		- m_Speed: 이동 속력
//
//		- player: 타 스크립트에서 참조를 위해 사용
//		- m_Triggered: 충돌 감지 여부
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

