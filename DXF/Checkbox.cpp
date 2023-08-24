#include "ComponentHeader.h"

CheckBox::CheckBox(string p_DefaultTextureName, string p_CheckedTextureName)
{
    m_DefaultTextureName = p_DefaultTextureName;
    m_CheckedTextureName = p_CheckedTextureName;
}

void CheckBox::Start()
{
    m_Sprite = GetComponentFromObject(gameObject, SpriteRenderer);
}

void CheckBox::OnMouseDown()
{
    m_isChecked = !m_isChecked;

    if (m_Sprite == nullptr) return;

    if (m_isChecked) m_Sprite->ChangeSprite(m_CheckedTextureName);
    else m_Sprite->ChangeSprite(m_DefaultTextureName);
}
