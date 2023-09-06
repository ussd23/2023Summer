#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class SpriteRenderer;
class MouseFunction;

class Scroll : public Component
{
public:
	void Start() override;

	SerializeFunction(Scroll)
	{
	}
	DeserializeFunction()
	{
	}
};