//-----------------------------------------------------------------------------
// File: SphereCollider
//
// Desc: ���� Collider
//
//		[Variables]
//		- radius: SphereCollider�� ũ�� (������)
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
	float		radius;

public:
	SphereCollider(float);

	void Update() override;
};

