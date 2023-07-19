//-----------------------------------------------------------------------------
// File: TextureManager
//
// Desc: 텍스쳐 인터페이스를 생성 및 반환하는 클래스
//
//		[Variables]
//		- m_Textures: 텍스쳐 인터페이스 목록
//		- m_TexturesMap: string 기반의 텍스쳐 인터페이스 목록
//
//		[Functions]
//		- GetTexture: 이미지 파일을 기반으로 텍스쳐 인터페이스를 검색하여 반환
//		- Cleanup: 텍스쳐 인터페이스 삭제
//-----------------------------------------------------------------------------

#pragma once
#include "StandardLibrary.h"
#include "GetI.h"
#include "DXHeader.h"


//DefClass(TextureManager)
class TextureManager : public GetI<TextureManager>
{
protected:
	vector<LPDIRECT3DTEXTURE9>		m_Textures;
	map<string, LPDIRECT3DTEXTURE9> m_TexturesMap;

public:
	LPDIRECT3DTEXTURE9 GetTexture(const string& p_Path);
	void Cleanup();
};

