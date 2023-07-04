//-----------------------------------------------------------------------------
// File: MouseFunction
//
// Desc: 마우스 입력 처리를 위한 컴포넌트
//		 (OnMouseEnter, OnMouseExit, OnMouseClick, OnMouseHold 사용 시 필요)
//
//		[Variables]
//		- entering: 마우스 오버가 되었는 지의 여부
//		- transform: 오브젝트의 Transform 컴포넌트
//		- bcollider: 오브젝트의 Boxcollider 컴포넌트
//		- scollider: 오브젝트의 SphereCollider 컴포넌트
//		- recttransform: 오브젝트의 Transform 컴포넌트 (collider 필요 없음)
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

