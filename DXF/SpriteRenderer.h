//-----------------------------------------------------------------------------
// File: SpriteRenderer
//
// Desc: 스프라이트 렌더를 위한 컴포넌트
//
//		[Variables]
//		- m_RectTransform: 오브젝트의 RectTransform 컴포넌트
//		- m_Texture: 텍스쳐 인터페이스
//		- m_TextureName: 텍스쳐의 파일명
//		- m_TextureSize: 텍스쳐의 크기
//		- m_Color: 텍스쳐의 색상
//		- m_RectSize: 텍스쳐 파일의 분할 개수
//		- m_RectIndex: 렌더링할 텍스쳐 파일의 인덱스
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
