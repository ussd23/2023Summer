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
private:
	SpriteRenderer* spr;
	MouseFunction* mouse;

public:
	Button(string _texturename, DWORD _color, Vector2 _rectsize, Vector2 _rectindex);

	void OnMouseDown() override;
	void OnMouseUp() override;

	void Start() override;
};
