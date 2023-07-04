//-----------------------------------------------------------------------------
// File: TextureManager
//
// Desc: 텍스쳐 인터페이스를 생성 및 반환하는 클래스
//
//		[Variables]
//		- textures: 텍스쳐 인터페이스 목록
//		- texturesmap: string 기반의 텍스쳐 인터페이스 목록
//
//		[Functions]
//		- GetTexture: 이미지 파일을 기반으로 텍스쳐 인터페이스를 검색하여 반환
//		- Cleanup: 텍스쳐 인터페이스 삭제
//-----------------------------------------------------------------------------

#pragma once
#include "StandardLibrary.h"
#include "GetI.h"
#include "DXHeader.h"

class TextureManager : public GetI<TextureManager>
{
protected:
	vector<LPDIRECT3DTEXTURE9>		textures;
	map<string, LPDIRECT3DTEXTURE9> texturesmap;

public:
	LPDIRECT3DTEXTURE9 GetTexture(string);
	void Cleanup();
};

