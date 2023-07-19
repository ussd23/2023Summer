//-----------------------------------------------------------------------------
// File: Collider
//
// Desc: Transform 컴포넌트를 사용하는 오브젝트의 충돌처리를 위해 필요한 컴포넌트
//		 BoxCollider 혹은 SphereCollider의 상위 클래스임
//
//		[Variables]
//		- m_Entering: 다른 Collider와 충돌중인 지의 여부
//		- m_PreSecond: 이전 충돌 체크 시간
//		- m_Transform: 오브젝트의 Transform 컴포넌트
//		- m_CheckTime: 충돌 체크 시간
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

