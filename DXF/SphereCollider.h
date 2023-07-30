//-----------------------------------------------------------------------------
// File: SphereCollider
//
// Desc: ���� Collider
//
//		[Variables]
//		- m_Radius: SphereCollider�� ũ�� (������)
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

	void Update() override;

	SerializeFunctions(SphereCollider);
};

