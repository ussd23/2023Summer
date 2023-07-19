//-----------------------------------------------------------------------------
// File: Collider
//
// Desc: Transform ������Ʈ�� ����ϴ� ������Ʈ�� �浹ó���� ���� �ʿ��� ������Ʈ
//		 BoxCollider Ȥ�� SphereCollider�� ���� Ŭ������
//
//		[Variables]
//		- m_Entering: �ٸ� Collider�� �浹���� ���� ����
//		- m_PreSecond: ���� �浹 üũ �ð�
//		- m_Transform: ������Ʈ�� Transform ������Ʈ
//		- m_CheckTime: �浹 üũ �ð�
//
//		[Functions]
//		- OnTrigger: �浹 ���� ���ο� ���� ��� ������Ʈ�� OnTriggerEnter,
//					 OnTriggerExit ����
//		- OnStay: �浹���� ������ ��� ��� ������Ʈ�� OnTriggerStay ����
//		- CollisionCheckBtoB: BoxCollider���� �浹 ����
//		- CollisionCheckBtoS: BoxCollider�� SphereCollider���� �浹 ����
//		- CollisionCheckStoS: SphereCollider���� �浹 ����
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class Transform;
class BoxCollider;
class SphereCollider;

class Collider : public Component
{
protected:
	map<Collider*, bool>		m_Entering;
	float						m_PreSecond;

public:
	Transform*					m_Transform;
	float						m_CheckTime = 0.1f;

protected:
	bool ColliderTimeCheck();

public:
	void OnTrigger(Collider* p_Collider, bool p_Result);
	void OnStay();

	static bool CollisionCheckBtoB(BoxCollider* p_Col1, BoxCollider* p_Col2);
	static bool CollisionCheckBtoS(BoxCollider* p_Col1, SphereCollider* p_Col2);
	static bool CollisionCheckStoS(SphereCollider* p_Col1, SphereCollider* p_Col2);

	void Start() override;
};

