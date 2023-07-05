//-----------------------------------------------------------------------------
// File: ObjectMove
//
// Desc: 움직일 수 있는 오브젝트의 이동을 위한 스크립트
//
//		[Variables]
//		- transform: 오브젝트의 Transform 컴포넌트
//		- movementvec: 이동 방향을 나타내는 벡터
//		- movespeed: 이동 속력
//		- length: movementvec의 길이
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"
#include "DXHeader.h"

class GameObject;
class Transform;

class ObjectMove : public Component
{
protected:
	Transform*		transform;
	D3DXVECTOR3		movementvec;
	float			movespeed;
	float			length = 0;

public:
	void Start() override;
	void Update() override;
};

