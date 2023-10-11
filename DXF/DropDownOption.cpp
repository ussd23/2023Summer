#include "ComponentHeader.h"

void DropDownOption::Start()
{
}

void DropDownOption::OnMouseDown()
{
    m_IsClicked = true;
}

void DropDownOption::OnMouseUp()
{
    if (m_IsClicked)
    {
        for (int i = 0; i < m_CallFNList.size(); i++)
        {
            m_CallFNList[i]->Interpret();
        }

        m_IsClicked = false;
    }
}