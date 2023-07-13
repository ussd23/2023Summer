//-----------------------------------------------------------------------------
// File: TopText
//
// Desc: ȭ�� ��ܿ� �ؽ�Ʈ�� ����ϱ� ���� ��ũ��Ʈ
//
//		[Variables]
//		- text: ������Ʈ�� TextRenderer ������Ʈ
//		- camera: ī�޶� ������Ʈ�� Camera ������Ʈ
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"

class GameObject;
class TextRenderer;
class Camera;

class TopText : public Component
{
protected:
	TextRenderer*		text;
	Camera*				camera;

public:
	void Start() override;
	void Update() override;

	void OnMouseDown() override;
};

