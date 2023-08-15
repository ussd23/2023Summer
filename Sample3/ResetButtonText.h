#pragma once
#include "Component.h"

class GameObject;
class TextRenderer;

class ResetButtonText : public Component
{
protected:
	TextRenderer*	m_TextRender;
	string			m_Text;

public:
	ResetButtonText(int Index);

	void Start() override;
	void Update() override;

	void SetText(string p_Text);

	SerializeFunction(ResetButtonText)
	{
		Serialize(m_Text);
	}
	DeserializeFunction()
	{
		Deserialize(m_Text);
	}
};

