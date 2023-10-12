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
// 
//		- m_isUnique: ȭ��� ���� ���� ǥ�õǴ� ������Ʈ�� �˻��ϴ� ����
//		  (RectTransform ��� �ÿ��� �����)
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
	bool								m_Result;
	bool								m_isEntering = false;
	Transform*							m_Transform;
	BoxCollider*						m_BoxCollider;
	SphereCollider*						m_SphereCollider;
	RectTransform*						m_RectTransform;

	static vector<pair<MouseFunction*, bool*>>	m_UniqueMouseFunctions;

public:
	bool								m_isUnique = false;

public:
	MouseFunction(const bool& p_isUnique);

	void Start() override;
	void PreUpdate() override;
	void Update() override;

	static void UniqueCheck();

	SerializeFunction(MouseFunction)
	{
		Serialize(m_isUnique);
	}
};

