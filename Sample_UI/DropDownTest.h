#pragma once
#include "Component.h"

class DropDownTest : public Component
{
private:
	DropDown* m_DropDown;

public:
	void Start() override;

	void func1();
	void func2();

	SerializeFunction(DropDownTest) {}
	DeserializeFunction() {}
};
