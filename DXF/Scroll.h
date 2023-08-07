#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class SpriteRenderer;
class MouseFunction;

class Scroll : public Component
{
private:
	SpriteRenderer* spr;
	MouseFunction* mouse;

public:
	Scroll();
	Scroll(Vector2, Vector2);
	Scroll(DWORD, Vector2, Vector2);

	void Start() override;
};

