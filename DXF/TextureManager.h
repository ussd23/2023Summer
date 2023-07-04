//-----------------------------------------------------------------------------
// File: TextureManager
//
// Desc: �ؽ��� �������̽��� ���� �� ��ȯ�ϴ� Ŭ����
//
//		[Variables]
//		- textures: �ؽ��� �������̽� ���
//		- texturesmap: string ����� �ؽ��� �������̽� ���
//
//		[Functions]
//		- GetTexture: �̹��� ������ ������� �ؽ��� �������̽��� �˻��Ͽ� ��ȯ
//		- Cleanup: �ؽ��� �������̽� ����
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

