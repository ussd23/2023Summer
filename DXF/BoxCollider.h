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

	void Update() override;
};

