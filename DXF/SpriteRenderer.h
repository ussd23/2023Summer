//-----------------------------------------------------------------------------
// File: SpriteRenderer
//
// Desc: ��������Ʈ ������ ���� ������Ʈ
//
//		[Variables]
//		- m_RectTransform: ������Ʈ�� RectTransform ������Ʈ
//		- m_Texture: �ؽ��� �������̽�
//		- m_TextureName: �ؽ����� ���ϸ�
//		- m_TextureSize: �ؽ����� ũ��
//		- m_Color: �ؽ����� ����
//		- m_RectSize: �ؽ��� ������ ���� ����
//		- m_RectIndex: �������� �ؽ��� ������ �ε���
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

class SpriteRenderer : public Renderer
{
protected:
	RectTransform*			m_RectTransform;
	LPDIRECT3DTEXTURE9		m_Texture = NULL;
	string					m_TextureName;
	RECT					m_TextureSize;

public:
	DWORD					m_Color;
	Vector2					m_RectSize;
	Vector2					m_RectIndex;

public:
	SpriteRenderer(string p_TextureName);
	SpriteRenderer(string p_TextureName, Vector2 p_RectSize, Vector2 p_RectIndex);
	SpriteRenderer(string p_TextureName, DWORD p_Color, Vector2 p_RectSize, Vector2 p_RectIndex);

	void Start() override;
	void PreRender() override;
	void Render() override;

	void ChangeSprite(string p_TextureName);

	SerializeFunction(SpriteRenderer)
	{
		Serialize(m_TextureName);
		Serialize(m_Color);
		Serialize(m_RectSize);
		Serialize(m_RectIndex);
	}
};
