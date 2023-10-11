#include "ComponentHeader.h"

void DropDown::Start()
{
	m_Sprite = GetComponentFromObject(gameObject, SpriteRenderer);
	m_NormalTexture = "";
	m_DropTexture = "";
}

void DropDown::OnMouseDown()
{
	m_IsClicked = true;
}

void DropDown::OnMouseUp()
{
	if (m_IsClicked)
	{
		if (m_Sprite == nullptr) return;

		if (m_IsDown == false)
		{
			m_Sprite->ChangeSprite(m_DropTexture);
			m_IsDown = true;
		}
		else
		{
			m_Sprite->ChangeSprite(m_NormalTexture);
			m_IsDown = false;
		}
		//옵션 활성화/비활성화 기능


		m_IsClicked = false;
	}
}
