//-----------------------------------------------------------------------------
// File: FontManager
//
// Desc: ��Ʈ �������̽��� ���� �� ��ȯ�ϴ� Ŭ����
//
//		[Variables]
//		- fonts: ��Ʈ �������̽� ���
//		- fonts: string ����� ��Ʈ �������̽� ���
//
//		[Functions]
//		- GetFont: ��Ʈ��� ����ũ�⸦ ������� ��Ʈ �������̽��� �˻��Ͽ� ��ȯ
//		- Cleanup: ��Ʈ �������̽� ����
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

