//-----------------------------------------------------------------------------
// File: SpriteRenderer
//
// Desc: ��������Ʈ ������ ���� ������Ʈ
//
//		[Variables]
//		- recttransform: ������Ʈ�� RectTransform ������Ʈ
//		- pTexture: �ؽ��� �������̽�
//		- texturename: �ؽ����� ���ϸ�
//		- texturesize: �ؽ����� ũ��
//		- color: �ؽ����� ����
//		- rectsize: �ؽ��� ������ ���� ����
//		- rectindex: �������� �ؽ��� ������ �ε���
//
//		[Functions]
//		- Render: ���� ����
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class RectTransform;

class SpriteRenderer : public Component
{
protected:
	RectTransform*			recttransform;
	LPDIRECT3DTEXTURE9		pTexture = NULL;
	string					texturename;
	RECT					texturesize;

public:
	DWORD					color;
	Vector2					rectsize;
	Vector2					rectindex;

public:
	SpriteRenderer(string);
	SpriteRenderer(string, Vector2, Vector2);
	SpriteRenderer(string, DWORD, Vector2, Vector2);
	void Render();

	void ChangeSprite(string p_Texturename);

	void Start() override;
};
