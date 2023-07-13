//-----------------------------------------------------------------------------
// File: TextRenderer
//
// Desc: 텍스트 렌더를 위한 컴포넌트
//
//		[Variables]
//		- recttransform: 오브젝트의 RectTransform 컴포넌트
//		- fontname: 폰트명
//		- size: 폰트 크기
//		- font: 폰트 인터페이스
//		- text: 출력할 텍스트
//		- format: 폰트 출력을 위한 포맷
//		- color: 폰트 색상
//
//		[Functions]
//		- Render: 렌더 실행
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

