#pragma once
#include "Component.h"

class GameObject;
class TextRenderer;

class BtnText : public Component
{
protected:
	TextRenderer*	m_TextRender;
	string			m_Text;

public:
	void Start() override;
	void Update() override;

	void SetText(string p_Text);

	SerializeFunction(BtnText)
	{
		Serialize(m_Text);
	}
	DeserializeFunction()
	{
		Deserialize(m_Text);
	}
};

