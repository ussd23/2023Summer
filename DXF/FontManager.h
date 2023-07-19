//-----------------------------------------------------------------------------
// File: FontManager
//
// Desc: ��Ʈ �������̽��� ���� �� ��ȯ�ϴ� Ŭ����
//
//		[Variables]
//		- m_Fonts: ��Ʈ �������̽� ���
//		- m_FontsMap: string ����� ��Ʈ �������̽� ���
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
	vector<LPD3DXFONT>		m_Fonts;
	map<string, LPD3DXFONT> m_FontsMap;

public:
	LPD3DXFONT GetFont(const string& p_FontName, const int& p_Size);
	void Cleanup();
};

