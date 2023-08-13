//-----------------------------------------------------------------------------
// File: TopText
//
// Desc: ȭ�� ��ܿ� �ؽ�Ʈ�� ����ϱ� ���� ��ũ��Ʈ
//
//		[Variables]
//		- m_Text ������Ʈ�� TextRenderer ������Ʈ
//		- m_Camera: ī�޶� ������Ʈ�� Camera ������Ʈ
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"

class GameObject;
class TextRenderer;
class Camera;

class TopText : public Component
{
protected:
	TextRenderer*		m_Text;

public:
	void Start() override;
	void Update() override;

	SerializeFunction(TopText) {}
	DeserializeFunction() {}
};

