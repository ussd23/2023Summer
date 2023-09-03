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

        childLT.x = childPos.x - (m_ChildRect->m_Size.x * 0.5);   //contentbox좌측변 좌표
        childLT.y = childPos.y - (m_ChildRect->m_Size.y * 0.5);   //contentbox상측변 좌표

        childRB.x = childPos.x + (m_ChildRect->m_Size.x * 0.5);   //contentbox우측변 좌표
        childRB.y = childPos.y + (m_ChildRect->m_Size.y * 0.5);   //contentbox하측변 좌표

        rectLT.x = pos.x - (m_Rect->m_Size.x * 0.5);      //viewbox좌측변 좌표
        rectLT.y = pos.y - (m_Rect->m_Size.y * 0.5);      //viewbox상측변 좌표

        rectRB.x = pos.x + (m_Rect->m_Size.x * 0.5);      //viewbox우측변 좌표
        rectRB.y = pos.y + (m_Rect->m_Size.y * 0.5);      //viewbox하측변 좌표

        //콘텐츠박스의 좌/우측변이 뷰박스의 좌/우측변의 밖에 있으면 x축이동 가능
        if (childLT.x < rectLT.x && childRB.x > rectRB.x)
        {
            Vector2 temppos = m_ChildRect->GetPosition();
            temppos.x = temppos.x + (Input::MousePosition.x - m_MousePrePos.x);
            m_ChildRect->SetPosition(temppos);
        }
        //콘텐츠박스의 좌/우측변이 뷰박스의 좌/우측변과 같으면 해당 방향으로의 이동만 제한
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

        //콘텐츠박스의 좌측변이 뷰박스의 좌측변의 안에 있으면 변 위치 맞춤
        if (childLT.x > rectLT.x)
        {
            gap.x = childLT.x - rectLT.x;

            Vector2 temppos = m_ChildRect->GetPosition();
            temppos.x -= gap.x;
            m_ChildRect->SetPosition(temppos);
        }
        //콘텐츠박스의 좌측변이 뷰박스의 좌측변의 안에 있으면 변 위치 맞춤
        if (childRB.x < rectRB.x)
        {
            gap.x = childRB.x - rectRB.x;

            Vector2 temppos = m_ChildRect->GetPosition();
            temppos.x -= gap.x;
            m_ChildRect->SetPosition(temppos);
        }

        //y축도 똑같이 해줌
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

    childLT.x = childPos.x - (m_ChildRect->m_Size.x * 0.5);   //contentbox좌측변 좌표
    childLT.y = childPos.y - (m_ChildRect->m_Size.y * 0.5);   //contentbox상측변 좌표

    childRB.x = childPos.x + (m_ChildRect->m_Size.x * 0.5);   //contentbox우측변 좌표
    childRB.y = childPos.y + (m_ChildRect->m_Size.y * 0.5);   //contentbox하측변 좌표

    rectLT.x = pos.x - (m_Rect->m_Size.x * 0.5);      //viewbox좌측변 좌표
    rectLT.y = pos.y - (m_Rect->m_Size.y * 0.5);      //viewbox상측변 좌표

    rectRB.x = pos.x + (m_Rect->m_Size.x * 0.5);      //viewbox우측변 좌표
    rectRB.y = pos.y + (m_Rect->m_Size.y * 0.5);      //viewbox하측변 좌표


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

    childLT.x = childPos.x - (m_ChildRect->m_Size.x * 0.5);   //contentbox좌측변 좌표
    childLT.y = childPos.y - (m_ChildRect->m_Size.y * 0.5);   //contentbox상측변 좌표

    childRB.x = childPos.x + (m_ChildRect->m_Size.x * 0.5);   //contentbox우측변 좌표
    childRB.y = childPos.y + (m_ChildRect->m_Size.y * 0.5);   //contentbox하측변 좌표

    rectLT.x = pos.x - (m_Rect->m_Size.x * 0.5);      //viewbox좌측변 좌표
    rectLT.y = pos.y - (m_Rect->m_Size.y * 0.5);      //viewbox상측변 좌표

    rectRB.x = pos.x + (m_Rect->m_Size.x * 0.5);      //viewbox우측변 좌표
    rectRB.y = pos.y + (m_Rect->m_Size.y * 0.5);      //viewbox하측변 좌표

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

//드래그로 이동, 마우스 휠로 이동 완료
//스크롤바 추가하기, 뷰박스 범위 넘어간 이미지 자르기 해야함5