#pragma once
#include "Component.h"

class ButtonTest : public Component
{
private:
	Button*			m_Button;

public:
	void Start() override;

	void func1();
	void func2();

	void AddCallFN(/*ButtonTest& p_classtarget, void(*m_CallFN)()*/);

	SerializeFunction(ButtonTest) {}
	DeserializeFunction() {}
};

