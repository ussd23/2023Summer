//-----------------------------------------------------------------------------
// File: SpriteRenderer
//
// Desc: ��������Ʈ ������ ���� ������Ʈ
//
//		[Variables]
//		- recttransform: ������Ʈ�� RectTransform ������Ʈ
//		- texturename: �ؽ����� ���ϸ�
//		- rectsize: �ؽ��� ������ ���� ����
//		- rectindex: �������� �ؽ��� ������ �ε���
//		- pTexture: �ؽ��� �������̽�
//		- pSprite: ��������Ʈ �������̽�
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

public:
	string					texturename;
	RECT					texturesize;
	D3DXVECTOR2				rectsize;
	D3DXVECTOR2				rectindex;
	LPDIRECT3DTEXTURE9		pTexture = NULL;

public:
	SpriteRenderer(GameObject*, string);
	SpriteRenderer(GameObject*, string, D3DXVECTOR2, D3DXVECTOR2);
	void Render();

	void Start() override;
};
