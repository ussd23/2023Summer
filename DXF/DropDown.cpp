#include "ComponentHeader.h"

void DropDown::Start()
{
	m_Sprite = GetComponentFromObject(gameObject, SpriteRenderer);
	m_NormalTexture = "system\\DropDownNormal.png";
	m_DropTexture = "system\\DropDownDown.png";
}

void DropDown::OnMouseDown()
{
	m_IsClicked = true;
}

void DropDown::OnMouseExit()
{
	m_IsClicked = false;
}

void DropDown::OnMouseUp()
{
	if (m_IsClicked)
	{
		if (m_IsDown == false)
		{
			SetToDown();
		}
		else
		{
			SetToNormal();
		}	
		m_IsClicked = false;
	}
}

void DropDown::SetToNormal()
{
	if (m_Sprite == nullptr) return;

	m_Sprite->ChangeSprite(m_NormalTexture);
	for (int i = 0; i < m_Options.size(); i++)
	{
		m_Options[i]->SetActive(false);
	}
	m_IsDown = false;
}

void DropDown::SetToDown()
{
	if (m_Sprite == nullptr) return;

	m_Sprite->ChangeSprite(m_DropTexture);
	for (int i = 0; i < m_Options.size(); i++)
	{
		m_Options[i]->SetActive(true);
	}
	m_IsDown = true;
}

string DropDown::GetCurText()
{
	return m_CurText;
}

void DropDown::SetCurText(string p_text)
{
	m_CurText = p_text;
}

void DropDown::SetChildRect()
{
	Vector2 temppos;
	RectTransform* optionRect;
	RectTransform* rect = GetComponentFromObject(gameObject, RectTransform);
	if (rect == nullptr) return;

	for (int i = 0; i < m_Options.size(); i++)
	{
		optionRect = GetComponentFromObject(m_Options[i], RectTransform);
		if (optionRect == nullptr) return;

		optionRect->m_Size = rect->m_Size;
		temppos = Vector2(20,0);
		temppos.y = temppos.y + (rect->m_Size.y * (i+1));
		optionRect->SetPosition(temppos);
	}

}
