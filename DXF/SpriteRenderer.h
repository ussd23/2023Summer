//-----------------------------------------------------------------------------
// File: SpriteRenderer
//
// Desc: ��������Ʈ ������ ���� ������Ʈ
//
//		[Variables]
//		- recttransform: ������Ʈ�� RectTransform ������Ʈ
//		- texturename: �ؽ����� ���ϸ�
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
	LPDIRECT3DTEXTURE9		pTexture = NULL;
	LPD3DXSPRITE			pSprite = NULL;

public:
	SpriteRenderer(GameObject*, string);
	void Render();

	void Start() override;
};
