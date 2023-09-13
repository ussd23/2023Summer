#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class SpriteRenderer;
class MouseFunction;

class Scroll : public Component
{
protected:
	bool m_IsVertical;

public:
	Scroll(bool p_IsVertical);

	void Start() override;

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