#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class MouseFunction;
class GameObject;
class TextRenderer;

class DropDownOption : public Component
{
protected:
	bool						m_IsClicked = false;
	DropDown*					m_DropDown;
	TextRenderer*				m_TextRender;
	string						m_Text;

public:
	vector<CCallBackBase*>		m_CallFNList;

public:
	void Start() override;

	void SetText(string p_Text);

	void OnMouseDown() override;
	void OnMouseExit() override;
	void OnMouseUp() override;

	SerializeFunction(DropDownOption) {}
	DeserializeFunction() {}
};
