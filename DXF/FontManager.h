//-----------------------------------------------------------------------------
// File: FontManager
//
// Desc: 폰트 인터페이스를 생성 및 반환하는 클래스
//
//		[Variables]
//		- fonts: 폰트 인터페이스 목록
//		- fonts: string 기반의 폰트 인터페이스 목록
//
//		[Functions]
//		- GetFont: 폰트명과 글자크기를 기반으로 폰트 인터페이스를 검색하여 반환
//		- Cleanup: 폰트 인터페이스 삭제
//-----------------------------------------------------------------------------

#pragma once
#include "StandardLibrary.h"
#include "GetI.h"
#include "DXHeader.h"

class FontManager : public GetI<FontManager>
{
protected:
	vector<LPD3DXFONT>		fonts;
	map<string, LPD3DXFONT> fontsmap;

public:
	LPD3DXFONT GetFont(const string&, const int&);
	void Cleanup();
};

