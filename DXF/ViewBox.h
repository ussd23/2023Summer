#pragma once

#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class SpriteRenderer;
class MouseFunction;

class ViewBox : public Component
{
private:
	SpriteRenderer*		m_Spr;
	MouseFunction*		m_Mouse;
	Vector2				m_MousePrePos;
	Vector2				m_MouseNowPos;
	bool				m_Isdown = false;
	RectTransform*		rect;
	RectTransform*		child;

public:
	ViewBox();
	ViewBox(Vector2, Vector2);
	ViewBox(DWORD, Vector2, Vector2);

	void OnMouseDown() override;
	void OnMouseUp() override;
	void OnMouseExit() override;
	void OnWheelUp() override;
	void OnWheelDown() override;

	void Start() override;
	void Update() override;
};
