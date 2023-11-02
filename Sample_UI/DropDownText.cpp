#include "Scripts.h"

void DropDownText::Start()
{
    m_Text = "";
    m_TextRender = GetComponentFromObject(gameObject, TextRenderer);

    RectTransform* thisrect = GetComponentFromObject(gameObject, RectTransform);
    RectTransform* parentrect = thisrect->GetParent();
    m_DropDown = GetComponentFromObject(parentrect->gameObject, DropDown);

    if (m_TextRender != nullptr) m_TextRender->m_Color = D3DCOLOR(0xff000000);
}

void DropDownText::Update()
{
    if (m_TextRender == nullptr) return;
    if (m_DropDown == nullptr) return;

    SetText(m_DropDown->GetCurText());

    stringstream temp;
    temp << m_Text;

    m_TextRender->m_Text = temp.str();
}

void DropDownText::SetText(string p_Text)
{
    m_Text = p_Text;
}

