#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

//�׳� recttransform spriterenderer mousefunction �ְ� ��ũ��Ʈ�ϳ� ���� ���콺����Լ� �������̵忡 �ݹ����ϸ� ��ư �ƴѰ�...
//�� ������ �ڵ����� ������Ʈ�� ����ϰ� ���� ������Ʈ�� �ؽ�Ʈ���� �ְ� ����� �ǳ�
//�ƴϸ� �� ���� �ڵ带 �� ���ٰ� ��ư�� ���� �������ϳ�

class RectTransform;
class SpriteRenderer;
class MouseFunction;

class Button : public Component
{
private:
	RectTransform* rect;
	SpriteRenderer* spr;
	MouseFunction* mouse;

public:
	Button(Vector2 _pos, Vector3 _rot, Vector2 _scale, Vector2 _size, string _texturename, DWORD _color, Vector2 _rectsize, Vector2 _rectindex);

	void InitBtn();
};
