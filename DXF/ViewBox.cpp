#include "ComponentHeader.h"

void ViewBox::Start()
{
    m_Rect = GetComponentFromObject(gameObject, RectTransform);

    if (m_Rect != nullptr)
    {
        if (m_Rect->GetChildCount() != 0)
        {
            m_ChildRect = m_Rect->GetChild(0);
        }
    }
}

void ViewBox::Update()
{
    if (m_ChildRect == nullptr) return;

    if (m_isDown)
    {
        Vector2 gap;
        Vector2 childLT, childRB, rectLT, rectRB;

        Vector2 pos = m_Rect->GetScreenPosition();
        Vector2 childPos = m_ChildRect->GetScreenPosition();

        childLT.x = childPos.x - (m_ChildRect->m_Size.x * 0.5);   //contentbox������ ��ǥ
        childLT.y = childPos.y - (m_ChildRect->m_Size.y * 0.5);   //contentbox������ ��ǥ

        childRB.x = childPos.x + (m_ChildRect->m_Size.x * 0.5);   //contentbox������ ��ǥ
        childRB.y = childPos.y + (m_ChildRect->m_Size.y * 0.5);   //contentbox������ ��ǥ

        rectLT.x = pos.x - (m_Rect->m_Size.x * 0.5);      //viewbox������ ��ǥ
        rectLT.y = pos.y - (m_Rect->m_Size.y * 0.5);      //viewbox������ ��ǥ

        rectRB.x = pos.x + (m_Rect->m_Size.x * 0.5);      //viewbox������ ��ǥ
        rectRB.y = pos.y + (m_Rect->m_Size.y * 0.5);      //viewbox������ ��ǥ

        //�������ڽ��� ��/�������� ��ڽ��� ��/�������� �ۿ� ������ x���̵� ����
        if (childLT.x < rectLT.x && childRB.x > rectRB.x)
        {
            Vector2 temppos = m_ChildRect->GetPosition();
            temppos.x = temppos.x + (Input::MousePosition.x - m_MousePrePos.x);
            m_ChildRect->SetPosition(temppos);
        }
        //�������ڽ��� ��/�������� ��ڽ��� ��/�������� ������ �ش� ���������� �̵��� ����
        else if (childLT.x == rectLT.x)
        {
            if (Input::MousePosition.x < m_MousePrePos.x)
            {
                Vector2 temppos = m_ChildRect->GetPosition();
                temppos.x = temppos.x + (Input::MousePosition.x - m_MousePrePos.x);
                m_ChildRect->SetPosition(temppos);
            }
        }
        else if (childRB.x == rectRB.x)
        {
            if (Input::MousePosition.x > m_MousePrePos.x)
            {
                Vector2 temppos = m_ChildRect->GetPosition();
                temppos.x = temppos.x + (Input::MousePosition.x - m_MousePrePos.x);
                m_ChildRect->SetPosition(temppos);
            }
        }

        //�������ڽ��� �������� ��ڽ��� �������� �ȿ� ������ �� ��ġ ����
        if (childLT.x > rectLT.x)
        {
            gap.x = childLT.x - rectLT.x;

            Vector2 temppos = m_ChildRect->GetPosition();
            temppos.x -= gap.x;
            m_ChildRect->SetPosition(temppos);
        }
        //�������ڽ��� �������� ��ڽ��� �������� �ȿ� ������ �� ��ġ ����
        if (childRB.x < rectRB.x)
        {
            gap.x = childRB.x - rectRB.x;

            Vector2 temppos = m_ChildRect->GetPosition();
            temppos.x -= gap.x;
            m_ChildRect->SetPosition(temppos);
        }

        //y�൵ �Ȱ��� ����
        if (childLT.y < rectLT.y && childRB.y > rectRB.y)
        {
            Vector2 temppos = m_ChildRect->GetPosition();
            temppos.y = temppos.y + (Input::MousePosition.y - m_MousePrePos.y);
            m_ChildRect->SetPosition(temppos);
        }
        else if (childLT.y == rectLT.y)
        {
            if (Input::MousePosition.y < m_MousePrePos.y)
            {
                Vector2 temppos = m_ChildRect->GetPosition();
                temppos.y = temppos.y + (Input::MousePosition.y - m_MousePrePos.y);
                m_ChildRect->SetPosition(temppos);
            }
        }
        else if (childRB.y == rectRB.y)
        {
            if (Input::MousePosition.y > m_MousePrePos.y)
            {
                Vector2 temppos = m_ChildRect->GetPosition();
                temppos.y = temppos.y + (Input::MousePosition.y - m_MousePrePos.y);
                m_ChildRect->SetPosition(temppos);
            }
        }

        if (childLT.y > rectLT.y)
        {
            gap.y = childLT.y - rectLT.y;

            Vector2 temppos = m_ChildRect->GetPosition();
            temppos.y -= gap.y;
            m_ChildRect->SetPosition(temppos);
        }
        if (childRB.y < rectRB.y)
        {
            gap.y = childRB.y - rectRB.y;

            Vector2 temppos = m_ChildRect->GetPosition();
            temppos.y -= gap.y;
            m_ChildRect->SetPosition(temppos);
        }

        m_MousePrePos = Input::MousePosition;
    }
}

void ViewBox::OnMouseDown()
{
    m_isDown = true;
    m_MousePrePos = Input::MousePosition;
}

void ViewBox::OnMouseUp()
{
    m_isDown = false;
}

void ViewBox::OnMouseExit()
{
    m_isDown = false;
}

void ViewBox::OnWheelUp()
{
    Vector2 gap;
    Vector2 childLT, childRB, rectLT, rectRB;

    Vector2 pos = m_Rect->GetScreenPosition();
    Vector2 childPos = m_ChildRect->GetScreenPosition();

    childLT.x = childPos.x - (m_ChildRect->m_Size.x * 0.5);   //contentbox������ ��ǥ
    childLT.y = childPos.y - (m_ChildRect->m_Size.y * 0.5);   //contentbox������ ��ǥ

    childRB.x = childPos.x + (m_ChildRect->m_Size.x * 0.5);   //contentbox������ ��ǥ
    childRB.y = childPos.y + (m_ChildRect->m_Size.y * 0.5);   //contentbox������ ��ǥ

    rectLT.x = pos.x - (m_Rect->m_Size.x * 0.5);      //viewbox������ ��ǥ
    rectLT.y = pos.y - (m_Rect->m_Size.y * 0.5);      //viewbox������ ��ǥ

    rectRB.x = pos.x + (m_Rect->m_Size.x * 0.5);      //viewbox������ ��ǥ
    rectRB.y = pos.y + (m_Rect->m_Size.y * 0.5);      //viewbox������ ��ǥ


    if (childLT.y < rectLT.y)
    {
        Vector2 temppos = m_ChildRect->GetPosition();
        temppos.y += 5;
        m_ChildRect->SetPosition(temppos);
    }

    if (childLT.y > rectLT.y)
    {
        gap.y = childLT.y - rectLT.y;

        Vector2 temppos = m_ChildRect->GetPosition();
        temppos.y -= gap.y;
        m_ChildRect->SetPosition(temppos);
    }
}

void ViewBox::OnWheelDown()
{
    Vector2 gap;
    Vector2 childLT, childRB, rectLT, rectRB;

    Vector2 pos = m_Rect->GetScreenPosition();
    Vector2 childPos = m_ChildRect->GetScreenPosition();

    childLT.x = childPos.x - (m_ChildRect->m_Size.x * 0.5);   //contentbox������ ��ǥ
    childLT.y = childPos.y - (m_ChildRect->m_Size.y * 0.5);   //contentbox������ ��ǥ

    childRB.x = childPos.x + (m_ChildRect->m_Size.x * 0.5);   //contentbox������ ��ǥ
    childRB.y = childPos.y + (m_ChildRect->m_Size.y * 0.5);   //contentbox������ ��ǥ

    rectLT.x = pos.x - (m_Rect->m_Size.x * 0.5);      //viewbox������ ��ǥ
    rectLT.y = pos.y - (m_Rect->m_Size.y * 0.5);      //viewbox������ ��ǥ

    rectRB.x = pos.x + (m_Rect->m_Size.x * 0.5);      //viewbox������ ��ǥ
    rectRB.y = pos.y + (m_Rect->m_Size.y * 0.5);      //viewbox������ ��ǥ

    if (childRB.y > rectRB.y)
    {
        Vector2 temppos = m_ChildRect->GetPosition();
        temppos.y -= 5;
        m_ChildRect->SetPosition(temppos);
    }

    if (childRB.y < rectRB.y)
    {
        gap.y = childRB.y - rectRB.y;

        Vector2 temppos = m_ChildRect->GetPosition();
        temppos.y -= gap.y;
        m_ChildRect->SetPosition(temppos);
    }
}

//�巡�׷� �̵�, ���콺 �ٷ� �̵� �Ϸ�
//��ũ�ѹ� �߰��ϱ�, ��ڽ� ���� �Ѿ �̹��� �ڸ��� �ؾ���5