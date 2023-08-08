#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

//�׳� recttransform spriterenderer mousefunction �ְ� ��ũ��Ʈ�ϳ� ���� ���콺����Լ� �������̵忡 �ݹ����ϸ� ��ư �ƴѰ�...
//�� ������ �ڵ����� ������Ʈ�� ����ϰ� ���� ������Ʈ�� �ؽ�Ʈ���� �ְ� ����� �ǳ�
//�ƴϸ� �� ���� �ڵ带 �� ���ٰ� ��ư�� ���� �������ϳ�

class SpriteRenderer;
class MouseFunction;

class Button : public Component
{
protected:
	SpriteRenderer*			m_Sprite;
	DWORD					m_DefaultColor;
	DWORD					m_PushedColor;

public:
	Button(DWORD p_DefaultColor, DWORD p_PushedColor);

	void OnMouseDown() override;
	void OnMouseUp() override;

	void Start() override;

	SerializeFunction(Button) {}
	DeserializeFunction() {}
};
