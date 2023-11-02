#include "ComponentHeader.h"

void DropDownOption::Start()
{
    RectTransform* thisrect = GetComponentFromObject(gameObject, RectTransform);
    RectTransform* parentrect = thisrect->GetParent();

    m_DropDown = GetComponentFromObject(parentrect->gameObject, DropDown);
    m_TextRender = GetComponentFromObject(gameObject, TextRenderer);

    if (m_TextRender != nullptr) 
    {
        m_TextRender->m_Color = D3DCOLOR(0xff000000);
        m_Text = m_TextRender->m_Text;
    }

    gameObject->SetActive(false);
}

void DropDownOption::SetText(string p_Text)
{
    if (m_TextRender == nullptr) return;
    m_Text = p_Text;

    stringstream temp;
    temp << m_Text;

    m_TextRender->m_Text = temp.str();
}

void DropDownOption::OnMouseDown()
{
    m_IsClicked = true;
}

void DropDownOption::OnMouseExit()
{
    m_IsClicked = false;
}

void DropDownOption::OnMouseUp()
{
    if (m_DropDown == nullptr) return;

    if (m_IsClicked)
    {
        for (int i = 0; i < m_CallFNList.size(); i++)
        {
            m_CallFNList[i]->Interpret();
        }

        m_DropDown->SetCurText(m_Text);
        m_DropDown->SetToNormal();
        m_IsClicked = false;
    }
}