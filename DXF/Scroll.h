#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class SpriteRenderer;
class MouseFunction;

class Scroll : public Component
{
protected:
	bool				m_IsVertical;
	bool				m_isDown = false;
	int					m_ClickTime;
	RectTransform*		m_ScrollBarRect;
	ViewBox*			m_ParentView;

public:
	Scroll(bool p_IsVertical);

	void Awake() override;
	void Start() override;

	void OnMouseDown() override;
	void OnMouseHold() override;
	void OnMouseUp() override;
	void OnMouseExit() override;

	bool GetIsVertical();

	void AdjustPosition();

	SerializeFunction(Scroll)
	{
		Serialize(m_IsVertical);
	}
	DeserializeFunction()
	{
		Deserialize(m_IsVertical);
	}
};