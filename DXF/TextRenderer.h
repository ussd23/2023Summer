//-----------------------------------------------------------------------------
// File: TextRenderer
//
// Desc: �ؽ�Ʈ ������ ���� ������Ʈ
//
//		[Variables]
//		- recttransform: ������Ʈ�� RectTransform ������Ʈ
//		- fontname: ��Ʈ��
//		- size: ��Ʈ ũ��
//		- font: ��Ʈ �������̽�
//		- text: ����� �ؽ�Ʈ
//		- format: ��Ʈ ����� ���� ����
//		- color: ��Ʈ ����
//
//		[Functions]
//		- Render: ���� ����
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class RectTransform;

class TextRenderer : public Component
{
protected:
	RectTransform*		recttransform;

public:
	string				fontname;
	int					size;
	LPD3DXFONT			font;
	string				text;
	DWORD				format;
	D3DCOLOR			color;

public:
	TextRenderer(string, int, string);
	TextRenderer(string, int, string, D3DCOLOR);
	TextRenderer(string, int, string, D3DCOLOR, DWORD);
	void Render();

	void Start() override;
};

