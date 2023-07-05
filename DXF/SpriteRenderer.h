//-----------------------------------------------------------------------------
// File: SpriteRenderer
//
// Desc: 스프라이트 렌더를 위한 컴포넌트
//
//		[Variables]
//		- recttransform: 오브젝트의 RectTransform 컴포넌트
//		- texturename: 텍스쳐의 파일명
//		- rectsize: 텍스쳐 파일의 분할 개수
//		- rectindex: 렌더링할 텍스쳐 파일의 인덱스
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
