//-----------------------------------------------------------------------------
// File: Collider
//
// Desc: Transform ������Ʈ�� ����ϴ� ������Ʈ�� �浹ó���� ���� �ʿ��� ������Ʈ
//		 BoxCollider Ȥ�� SphereCollider�� ���� Ŭ������
//
//		[Variables]
//		- entering: �ٸ� Collider�� �浹���� ���� ����
//		- presecond: ���� �浹 üũ �ð�
//		- transform: ������Ʈ�� Transform ������Ʈ
//		- collidertime: �浹 üũ �ð�
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
	map<Collider*, bool>		entering;
	float						presecond;

public:
	Transform*					transform;
	float						collidertime = 0.1f;

protected:
	bool ColliderTimeCheck();

public:
	void OnTrigger(Collider*, bool);
	void OnStay();

	static bool CollisionCheckBtoB(BoxCollider*, BoxCollider*);
	static bool CollisionCheckBtoS(BoxCollider*, SphereCollider*);
	static bool CollisionCheckStoS(SphereCollider*, SphereCollider*);

	void Start() override;
};

