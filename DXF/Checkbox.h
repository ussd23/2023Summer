#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class SpriteRenderer;
class MouseFunction;

class Checkbox : public Component
{
private:
	SpriteRenderer*			spr;
	MouseFunction*			mouse;
	string					texturename[2];
	int						textureindex;

public:
	Checkbox();
	Checkbox(Vector2, Vector2);
	Checkbox(DWORD, Vector2, Vector2);

	void OnMouseDown() override;

	void Start() override;
};

