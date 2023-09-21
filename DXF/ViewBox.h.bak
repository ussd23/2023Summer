#pragma once

#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class SpriteRenderer;
class MouseFunction;

class ViewBox : public Component
{
private:
	Vector2				m_MousePrePos;
	bool				m_isDown = false;
	RectTransform*		m_Rect;
	RectTransform*		m_ChildRect;

public:
	void OnMouseDown() override;
	void OnMouseUp() override;
	void OnMouseExit() override;
	void OnWheelUp() override;
	void OnWheelDown() override;

	void Start() override;
	void Update() override;

	SerializeFunction(ViewBox) {}
	DeserializeFunction() {}
};
