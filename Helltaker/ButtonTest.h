#pragma once
#include "Component.h"

class ButtonTest : public Component
{
private:

public:
	static void func1();
	void OnMouseDown() override;
};

