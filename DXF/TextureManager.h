//-----------------------------------------------------------------------------
// File: TextureManager
//
// Desc: �ؽ��� �������̽��� ���� �� ��ȯ�ϴ� Ŭ����
//
//		[Variables]
//		- m_Textures: �ؽ��� �������̽� ���
//		- m_TexturesMap: string ����� �ؽ��� �������̽� ���
//
//		[Functions]
//		- GetTexture: �̹��� ������ ������� �ؽ��� �������̽��� �˻��Ͽ� ��ȯ
//		- Cleanup: �ؽ��� �������̽� ����
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

