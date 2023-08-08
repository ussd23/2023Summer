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

    m_Sprite->m_Color = 0xff808080;
}

void Button::OnMouseUp()
{
    if (m_Sprite == nullptr) return;

    m_Sprite->m_Color = 0xffffffff;
}
