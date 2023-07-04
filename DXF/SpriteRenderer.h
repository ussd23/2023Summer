//-----------------------------------------------------------------------------
// File: SpriteRenderer
//
// Desc: 스프라이트 렌더를 위한 컴포넌트
//
//		[Variables]
//		- recttransform: 오브젝트의 RectTransform 컴포넌트
//		- texturename: 텍스쳐의 파일명
//		- pTexture: 텍스쳐 인터페이스
//		- pSprite: 스프라이트 인터페이스
//
//		[Functions]
//		- Render: 렌더 실행
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
