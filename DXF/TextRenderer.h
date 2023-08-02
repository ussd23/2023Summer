//-----------------------------------------------------------------------------
// File: TextRenderer
//
// Desc: �ؽ�Ʈ ������ ���� ������Ʈ
//
//		[Variables]
//		- m_RectTransform: ������Ʈ�� RectTransform ������Ʈ
//		- m_Rect: �ؽ�Ʈ�� ����� ����
//		- m_FontName: ��Ʈ��
//		- m_FontSize: ��Ʈ ũ��
//		- m_Font: ��Ʈ �������̽�
//		- m_Text: ����� �ؽ�Ʈ
//		- m_Format: ��Ʈ ����� ���� ����
//		- m_Color: ��Ʈ ����
//
//		[Functions]
//		- Render: ���� ����
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

