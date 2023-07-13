//-----------------------------------------------------------------------------
// File: PlayerMove
//
// Desc: 플레이어 오브젝트의 이동을 위한 스크립트
//
//		[Variables]
//		- transform: 오브젝트의 Transform 컴포넌트
//		- movespeed: 이동 속력
//
//		- player: 타 스크립트에서 참조를 위해 사용
//		- length: 충돌 감지 여부
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

