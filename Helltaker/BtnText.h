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
	BtnText();

	void Start() override;
	void Update() override;

	void SetText(string p_Text);
};

