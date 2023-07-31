//spriterenderer대신 넣으면 됨
//텍스쳐 두개 사이에서 왔다갔다 할테니까 생성자에서 텍스쳐 이름 뺌

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

