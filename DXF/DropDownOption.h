#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class SpriteRenderer;
class MouseFunction;

class DropDownOption : public Component
{
protected:
	bool							m_IsClicked = false;

public:
	vector<CCallBackBase*> m_CallFNList;

public:
	void Start() override;

	void OnMouseDown() override;
	void OnMouseUp() override;

	SerializeFunction(DropDownOption) {}
	DeserializeFunction() {}
};
