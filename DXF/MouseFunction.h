//-----------------------------------------------------------------------------
// File: MouseFunction
//
// Desc: ���콺 �Է� ó���� ���� ������Ʈ
//		 (OnMouseEnter, OnMouseExit, OnMouseClick, OnMouseHold ��� �� �ʿ�)
//
//		[Variables]
//		- entering: ���콺 ������ �Ǿ��� ���� ����
//		- transform: ������Ʈ�� Transform ������Ʈ
//		- bcollider: ������Ʈ�� Boxcollider ������Ʈ
//		- scollider: ������Ʈ�� SphereCollider ������Ʈ
//		- recttransform: ������Ʈ�� Transform ������Ʈ (collider �ʿ� ����)
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"
#include "DXHeader.h"

class Transform;
class RectTransform;
class BoxCollider;
class SphereCollider;

class MouseFunction : public Component
{
protected:
	bool				entering = false;
	Transform*			transform;
	BoxCollider*		bcollider;
	SphereCollider*		scollider;
	RectTransform*		recttransform;

public:
	void Start() override;
	void Update() override;
};

