#pragma once
#include "Component.h"

class ButtonTest : public Component
{
private:
	vector<CCallBackBase*> m_CallFNList;

public:
	void func1();
	void func2();
	void OnMouseUp() override;

	void AddCallFN(/*ButtonTest& p_classtarget, void(*m_CallFN)()*/);

	SerializeFunction(ButtonTest) {}
};

