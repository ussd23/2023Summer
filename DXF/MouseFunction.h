//-----------------------------------------------------------------------------
// File: MouseFunction
//
// Desc: 마우스 입력 처리를 위한 컴포넌트
//		 (OnMouse... 사용 시 필요)
//
//		[Variables]
//		- m_isEntering: 마우스 오버가 되었는 지의 여부
//		- m_Transform: 오브젝트의 Transform 컴포넌트
//		- m_BoxCollider: 오브젝트의 Boxcollider 컴포넌트
//		- m_SphereCollider: 오브젝트의 SphereCollider 컴포넌트
//		- m_Recttransform: 오브젝트의 Transform 컴포넌트 (collider 필요 없음)
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
	bool				m_isEntering = false;
	Transform*			m_Transform;
	BoxCollider*		m_BoxCollider;
	SphereCollider*		m_SphereCollider;
	RectTransform*		m_RectTransform;

public:
	void Start() override;
	void Update() override;

	SerializeFunction(MouseFunction)
	{
	}
	DeserializeFunction()
	{
	}
};

