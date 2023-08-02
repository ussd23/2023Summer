//-----------------------------------------------------------------------------
// File: MouseFunction
//
// Desc: ���콺 �Է� ó���� ���� ������Ʈ
//		 (OnMouse... ��� �� �ʿ�)
//
//		[Variables]
//		- m_isEntering: ���콺 ������ �Ǿ��� ���� ����
//		- m_Transform: ������Ʈ�� Transform ������Ʈ
//		- m_BoxCollider: ������Ʈ�� Boxcollider ������Ʈ
//		- m_SphereCollider: ������Ʈ�� SphereCollider ������Ʈ
//		- m_Recttransform: ������Ʈ�� Transform ������Ʈ (collider �ʿ� ����)
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

