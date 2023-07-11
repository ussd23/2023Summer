//-----------------------------------------------------------------------------
// File: BoxCollider
//
// Desc: ����ü�� Collider
//
//		[Variables]
//		- size: Collider�� ũ�� (x: width, y: height, z: depth)
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
	Vector3			size;

public:
	BoxCollider(Vector3);

	void Update() override;
};

