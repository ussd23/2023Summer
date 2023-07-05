//-----------------------------------------------------------------------------
// File: SpriteRenderer
//
// Desc: 스프라이트 렌더를 위한 컴포넌트
//
//		[Variables]
//		- recttransform: 오브젝트의 RectTransform 컴포넌트
//		- pTexture: 텍스쳐 인터페이스
//		- texturename: 텍스쳐의 파일명
//		- texturesize: 텍스쳐의 크기
//		- color: 텍스쳐의 색상
//		- rectsize: 텍스쳐 파일의 분할 개수
//		- rectindex: 렌더링할 텍스쳐 파일의 인덱스
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
