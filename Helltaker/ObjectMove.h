//-----------------------------------------------------------------------------
// File: ObjectMove
//
// Desc: 움직일 수 있는 오브젝트의 이동을 위한 스크립트
//
//		[Variables]
//		- m_Transform: 오브젝트의 Transform 컴포넌트
//		- m_MovementVec: 이동 방향을 나타내는 벡터
//		- m_Speed: 이동 속력
//		- m_Length: m_MovementVec의 길이
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"
#include "DXHeader.h"

class GameObject;
class Transform;

class ObjectMove : public Component
{
protected:
	Transform*		m_Transform;
	Vector3			m_MovementVec;
	float			m_Speed;
	float			m_Length = 0;

public:
	void Start() override;
	void Update() override;
};

