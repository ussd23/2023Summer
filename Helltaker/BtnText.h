#pragma once
#include "Component.h"

class GameObject;
class TextRenderer;

class BtnText : public Component
{
protected:
	TextRenderer* text;

public:
	void Start() override;
	void Update() override;
};

