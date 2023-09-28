#pragma once
#include "Component.h"

class ResetButton : public Component
{
private:
	vector<CCallBackBase*> m_CallFNList;
	class Minesweeper* MineSweeper;
	int Index = 0;

public:
	ResetButton(class Minesweeper* Sweeper, int Index);

	void func1();
	void func2();
	void func3();
	void OnMouseUp() override;

	void AddCallFN(/*ButtonTest& p_classtarget, void(*m_CallFN)()*/);

	SerializeFunction(ResetButton) {}
};

