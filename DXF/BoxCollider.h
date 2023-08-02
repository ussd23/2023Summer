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

public:
	BoxCollider(const Vector3& p_Size);
	BoxCollider(const Vector3& p_Size, bool p_isPassive);
	BoxCollider(const Vector3& p_Size, bool p_isPassive, bool p_isFixedChecking);
	BoxCollider(const Vector3& p_Size, bool p_isPassive, bool p_isFixedChecking, float p_CheckTime);

	void Update() override;

	SerializeFunction(BoxCollider)
	{
		Serialize(m_Size);
		Serialize(m_isPassive);
		Serialize(m_isFixedChecking);
		Serialize(m_CheckTime);
	}
	DeserializeFunction()
	{
		Deserialize(m_Size);
		Deserialize(m_isPassive);
		Deserialize(m_isFixedChecking);
		Deserialize(m_CheckTime);
	}
};

