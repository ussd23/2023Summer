//-----------------------------------------------------------------------------
// File: SphereCollider
//
// Desc: 구형 Collider
//
//		[Variables]
//		- radius: SphereCollider의 크기 (반지름)
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

