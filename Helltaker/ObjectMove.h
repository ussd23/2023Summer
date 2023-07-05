//-----------------------------------------------------------------------------
// File: ObjectMove
//
// Desc: ������ �� �ִ� ������Ʈ�� �̵��� ���� ��ũ��Ʈ
//
//		[Variables]
//		- transform: ������Ʈ�� Transform ������Ʈ
//		- movementvec: �̵� ������ ��Ÿ���� ����
//		- movespeed: �̵� �ӷ�
//		- length: movementvec�� ����
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

