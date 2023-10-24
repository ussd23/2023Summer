#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class SpriteRenderer;
class MouseFunction;

class Button : public Component
{
protected:
	SpriteRenderer*			m_Sprite;
	DWORD						m_DefaultColor = 0xff808080;
	DWORD						m_PushedColor = 0xffffffff;
	bool							m_IsClicked = false;

public:
	vector<CCallBackBase*> m_CallFNList;

public:
	Button(DWORD p_DefaultColor, DWORD p_PushedColor);

	void Start() override;

	void OnMouseDown() override;
	void OnMouseExit() override;
	void OnMouseUp() override;

	SerializeFunction(Button) {}
	DeserializeFunction() {}
};
