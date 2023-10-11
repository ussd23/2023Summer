#include "ComponentHeader.h"

Button::Button(DWORD p_DefaultColor, DWORD p_PushedColor)
    : m_DefaultColor(p_DefaultColor), m_PushedColor(p_PushedColor) {}

void Button::Start()
{
    m_Sprite = GetComponentFromObject(gameObject, SpriteRenderer);
}

void Button::OnMouseDown()
{
    if (m_Sprite == nullptr) return;

    m_Sprite->m_Color = m_DefaultColor;

    m_IsClicked = true;
}

void Button::OnMouseUp()
{
    if (m_IsClicked)
    {
        if (m_Sprite == nullptr) return;

        m_Sprite->m_Color = m_PushedColor;

        for (int i = 0; i < m_CallFNList.size(); i++)
        {
            m_CallFNList[i]->Interpret();
        }

        m_IsClicked = false;
    }
}
