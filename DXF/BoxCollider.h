//-----------------------------------------------------------------------------
// File: BoxCollider
//
// Desc: 육면체형 Collider
//
//		[Variables]
//		- m_Size: Collider의 크기 (x: width, y: height, z: depth)
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"
#include "Collider.h"

class Transform;

class BoxCollider : public Collider
{
public:
	Vector3			m_Size;
	Vector3			m_HalfSize;
	Vector3			m_AxisX;
	Vector3			m_AxisY;
	Vector3			m_AxisZ;

public:
	BoxCollider(const Vector3& p_Size);
	BoxCollider(const Vector3& p_Size, bool p_isPassive);
	BoxCollider(const Vector3& p_Size, bool p_isPassive, bool p_isFixedChecking);
	BoxCollider(const Vector3& p_Size, bool p_isPassive, bool p_isFixedChecking, float p_CheckTime);

	void PreUpdate() override;
	void Update() override;

	SerializeFunction(BoxCollider)
	{
		Serialize(m_Size);
		Serialize(m_isPassive);
		Serialize(m_isFixedChecking);
		Serialize(m_CheckTime);
	}
};

