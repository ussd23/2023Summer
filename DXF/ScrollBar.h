#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class SpriteRenderer;
class MouseFunction;

class ScrollBar : public Component
{
protected:
	Vector2 m_MovableRange[2];
	float normal;

public:
	void Awake() override;
	void Start() override;

	SerializeFunction(ScrollBar)
	{
	}
	DeserializeFunction()
	{
	}
};