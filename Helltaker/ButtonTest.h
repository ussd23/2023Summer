#pragma once
#include "Component.h"

class ButtonTest : public Component
{
private:
	vector<CCallBackBase*> m_CallFNList;

public:
	void func1();
	void func2();
	void OnMouseDown() override;

	void AddCallFN(/*ButtonTest& p_classtarget, void(*m_CallFN)()*/);
};

