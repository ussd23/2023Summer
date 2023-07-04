//-----------------------------------------------------------------------------
// File: Collider
//
// Desc: Transform ������Ʈ�� ����ϴ� ������Ʈ�� �浹ó���� ���� �ʿ��� ������Ʈ
//		 BoxCollider Ȥ�� SphereCollider�� ���� Ŭ������
//
//		[Variables]
//		- transform: ������Ʈ�� Transform ������Ʈ
//		- entering: �ٸ� Collider�� �浹���� ���� ����
//		- radius: Collider�� ũ�� (������)
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
	Transform*					transform;
	map<Collider*, bool>		entering;

public:
	void OnTrigger(Collider*, bool);
	void OnStay();

	static bool CollisionCheckBtoB(BoxCollider*, BoxCollider*);
	static bool CollisionCheckBtoS(BoxCollider*, SphereCollider*);
	static bool CollisionCheckStoS(SphereCollider*, SphereCollider*);

	void Start() override;
};

