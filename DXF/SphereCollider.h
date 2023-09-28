//-----------------------------------------------------------------------------
// File: SphereCollider
//
// Desc: 구형 Collider
//
//		[Variables]
//		- m_Radius: SphereCollider의 크기 (반지름)
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"
#include "Collider.h"

class Transform;

class SphereCollider : public Collider
{
public:
	float		m_Radius;

public:
	SphereCollider(const float& p_Radius);
	SphereCollider(const float& p_Radius, bool p_isPassive);
	SphereCollider(const float& p_Radius, bool p_isPassive, bool p_isFixedChecking);
	SphereCollider(const float& p_Radius, bool p_isPassive, bool p_isFixedChecking, float p_CheckTime);

	void Update() override;

	SerializeFunction(SphereCollider)
	{
		Serialize(m_Radius);
		Serialize(m_isPassive);
		Serialize(m_isFixedChecking);
		Serialize(m_CheckTime);
	}
};

