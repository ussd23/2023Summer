#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class SpriteRenderer;
class MouseFunction;

class ScrollBar : public Component
{
protected:
	Vector2				m_MousePrePos;
	bool					m_isDown = false;
	RectTransform*		m_Rect;
	ViewBox*			m_ParentView;
	Scroll*				m_ParentScroll;

public:
	void Awake() override;
	void Start() override;
	void Update() override;

	void OnMouseDown() override;
	void OnMouseUp() override;
	void OnMouseExit() override;

	void MoveScrollBar();

	SerializeFunction(ScrollBar)
	{
	}
	DeserializeFunction()
	{
	}
};