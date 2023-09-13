#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class SpriteRenderer;
class MouseFunction;

class ScrollBar : public Component
{
public:
	void Start() override;

	SerializeFunction(ScrollBar)
	{
	}
	DeserializeFunction()
	{
	}
};