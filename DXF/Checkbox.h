//spriterenderer��� ������ ��
//�ؽ��� �ΰ� ���̿��� �Դٰ��� ���״ϱ� �����ڿ��� �ؽ��� �̸� ��

#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class RectTransform;

class Checkbox : public Component
{
protected:
	RectTransform*			recttransform;
	LPDIRECT3DTEXTURE9		pTexture = NULL;
	string					texturename[2];
	RECT					texturesize;
	int						textureindex;

public:
	DWORD					color;
	Vector2					rectsize;
	Vector2					rectindex;

public:
	Checkbox();
	Checkbox(Vector2, Vector2);
	Checkbox(DWORD, Vector2, Vector2);
	void Render();

	void OnMouseDown() override;

	void Start() override;
};

