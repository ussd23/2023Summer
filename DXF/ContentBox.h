#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class SpriteRenderer;
class MouseFunction;

class ContentBox : public Component
{
private:
	SpriteRenderer*		spr;
	MouseFunction*		mouse;

public:
	ContentBox();
	ContentBox(Vector2, Vector2);
	ContentBox(DWORD, Vector2, Vector2);

	void Start() override;
};

