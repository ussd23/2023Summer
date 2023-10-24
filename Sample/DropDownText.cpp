#include "Scripts.h"

void DropDownText::Start()
{
    m_Text = "";
    m_TextRender = GetComponentFromObject(gameObject, TextRenderer);
    m_DropDown = GetComponentFromObject(gameObject, DropDown);
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

