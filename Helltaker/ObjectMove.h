//-----------------------------------------------------------------------------
// File: ObjectMove
//
// Desc: ������ �� �ִ� ������Ʈ�� �̵��� ���� ��ũ��Ʈ
//
//		[Variables]
//		- m_Transform: ������Ʈ�� Transform ������Ʈ
//		- m_MovementVec: �̵� ������ ��Ÿ���� ����
//		- m_Speed: �̵� �ӷ�
//		- m_Length: m_MovementVec�� ����
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

