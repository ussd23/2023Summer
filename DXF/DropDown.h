#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class SpriteRenderer;
class MouseFunction;

class DropDown : public Component
{
protected:
	bool						m_IsClicked = false;
	bool						m_IsDown = false;
	string						m_CurText;
	string						m_NormalTexture;
	string						m_DropTexture;
	SpriteRenderer*				m_Sprite;

public:
	vector<GameObject*>			m_Options;

public:
	void Start() override;

	void OnMouseDown() override;
	void OnMouseExit() override;
	void OnMouseUp() override;

	void SetToNormal();
	void SetToDown();
	string GetCurText();
	void SetCurText(string p_text);
	void SetChildRect();

	SerializeFunction(DropDown) {}
	DeserializeFunction() {}
};
