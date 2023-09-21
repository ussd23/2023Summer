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
	RectTransform*		m_ContentRect;
	RectTransform*		m_VScrollRect;
	RectTransform*		m_VScrollBarRect;
	RectTransform*		m_HScrollRect;
	RectTransform*		m_HScrollBarRect;
	Vector2				m_PreContentPos;
	Vector2				m_PreScrollBarPos;
	Vector2				m_ContentMinRange;
	Vector2				m_ContentMaxRange;
	Vector2				m_ScrollBarMinRange;
	Vector2				m_ScrollBarMaxRange;

public:
	void Start() override;
	void Update() override;

	void OnMouseDown() override;
	void OnMouseUp() override;
	void OnMouseExit() override;
	void OnWheelUp() override;
	void OnWheelDown() override;

	void MoveContentBox();
	void UpdateContentBox();
	void UpdateScrollBar();
	void CalcScrollMovableRange();
	void CalcContentMovableRange();
	Vector2 NormalizePosition(Vector2 p_CurrentPos, Vector2 p_MinPos, Vector2 p_MaxPos);
	Vector2 DisNormalizePosition(Vector2 p_Normal, Vector2 p_MinPos, Vector2 p_MaxPos);
	Vector2 GetScrollBarMinRange();
	Vector2 GetScrollBarMaxRange();

	SerializeFunction(ViewBox) {}
	DeserializeFunction() {}
};
