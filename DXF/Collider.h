//-----------------------------------------------------------------------------
// File: Collider
//
// Desc: Transform 컴포넌트를 사용하는 오브젝트의 충돌처리를 위해 필요한 컴포넌트
//		 BoxCollider 혹은 SphereCollider의 상위 클래스임
//
//		[Variables]
//		- entering: 다른 Collider와 충돌중인 지의 여부
//		- presecond: 이전 충돌 체크 시간
//		- transform: 오브젝트의 Transform 컴포넌트
//		- collidertime: 충돌 체크 시간
//
//		[Functions]
//		- OnTrigger: 충돌 갱신 여부에 따라 모든 컴포넌트의 OnTriggerEnter,
//					 OnTriggerExit 수행
//		- OnStay: 충돌중인 상태의 경우 모든 컴포넌트의 OnTriggerStay 수행
//		- CollisionCheckBtoB: BoxCollider간의 충돌 여부
//		- CollisionCheckBtoS: BoxCollider와 SphereCollider간의 충돌 여부
//		- CollisionCheckStoS: SphereCollider간의 충돌 여부
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

