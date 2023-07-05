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
	D3DXVECTOR2				rectsize;
	D3DXVECTOR2				rectindex;

public:
	SpriteRenderer(GameObject*, string);
	SpriteRenderer(GameObject*, string, D3DXVECTOR2, D3DXVECTOR2);
	SpriteRenderer(GameObject*, string, DWORD, D3DXVECTOR2, D3DXVECTOR2);
	void Render();

	void Start() override;
};
