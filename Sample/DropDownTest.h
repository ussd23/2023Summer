#pragma once
#include "Component.h"

class DropDownTest : public Component
{
private:
	DropDown* m_DropDown;

public:
	void Start() override;

	SerializeFunction(DropDownTest) {}
	DeserializeFunction() {}
};
