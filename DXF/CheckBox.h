#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class SpriteRenderer;
class MouseFunction;

class CheckBox : public Component
{
protected:
	SpriteRenderer*			m_Sprite;

	string					m_DefaultTextureName;
	string					m_CheckedTextureName;
	bool					m_isChecked = false;

public:
	CheckBox(string p_DefaultTextureName, string p_CheckedTextureName);

	void OnMouseDown() override;

	void Start() override;

	SerializeFunction(CheckBox)
	{
		Serialize(m_DefaultTextureName);
		Serialize(m_CheckedTextureName);
		Serialize(m_isChecked);
	}
};

