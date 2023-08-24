//-----------------------------------------------------------------------------
// File: TextRenderer
//
// Desc: 텍스트 렌더를 위한 컴포넌트
//
//		[Variables]
//		- m_RectTransform: 오브젝트의 RectTransform 컴포넌트
//		- m_Rect: 텍스트를 출력할 범위
//		- m_FontName: 폰트명
//		- m_FontSize: 폰트 크기
//		- m_Font: 폰트 인터페이스
//		- m_Text: 출력할 텍스트
//		- m_Format: 폰트 출력을 위한 포맷
//		- m_Color: 폰트 색상
//
//		[Functions]
//		- Render: 렌더 실행
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"
#include "Renderer.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class RectTransform;

class TextRenderer : public Renderer
{
protected:
	RectTransform*		m_RectTransform;
	RECT				m_Rect;

public:
	string				m_FontName;
	int					m_FontSize;
	LPD3DXFONT			m_Font;
	string				m_Text;
	DWORD				m_Format;
	D3DCOLOR			m_Color;

public:
	TextRenderer(string p_FontName, int p_FontSize, string p_Text);
	TextRenderer(string p_FontName, int p_FontSize, string p_Text, D3DCOLOR p_Color);
	TextRenderer(string p_FontName, int p_FontSize, string p_Text, D3DCOLOR p_Color, DWORD p_Format);

	void Start() override;
	void PreRender() override;
	void Render() override;

	SerializeFunction(TextRenderer)
	{
		Serialize(m_FontName);
		Serialize(m_FontSize);
		Serialize(m_Text);
		Serialize(m_Format);
		Serialize(m_Color);
	}
	DeserializeFunction()
	{
		Deserialize(m_FontName);
		Deserialize(m_FontSize);
		Deserialize(m_Text);
		Deserialize(m_Format);
		Deserialize(m_Color);
	}
};

