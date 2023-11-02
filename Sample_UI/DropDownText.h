#pragma once
#include "Component.h"

class GameObject;
class TextRenderer;

class DropDownText : public Component
{
protected:
	DropDown*		m_DropDown;
	TextRenderer*	m_TextRender;
	string			m_Text;

public:
	void Start() override;
	void Update() override;

	void SetText(string p_Text);

	SerializeFunction(DropDownText)
	{
		Serialize(m_Text);
	}
	DeserializeFunction()
	{
		Deserialize(m_Text);
	}
};

