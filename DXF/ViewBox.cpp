#include "ComponentHeader.h"

void ViewBox::Start()
{
    m_Rect = GetComponentFromObject(gameObject, RectTransform);

    //contentbox와 scroll관련 오브젝트들의 recttranceform정보 미리 받아둠
    if (m_Rect != nullptr)
    {
        int cnt = m_Rect->GetChildCount();
        for (int i=0; i< cnt; i++)
        {
            RectTransform* ChildRect = m_Rect->GetChild(i);
            if (ChildRect->gameObject->m_Name.compare("contentbox") == 0)
            {
                m_ContentRect = ChildRect;
            }
            else if (ChildRect->gameObject->m_Name.compare("VerticalScroll") == 0)
            {
                m_VScrollRect = ChildRect;
            }
            else if (ChildRect->gameObject->m_Name.compare("HorizontalScroll") == 0)
            {
                m_HScrollRect = ChildRect;
            }
        }

        if (m_VScrollRect != nullptr)
        {
            int cnt = m_VScrollRect->GetChildCount();
            for (int i = 0; i < cnt; i++)
            {
                RectTransform* ChildRect = m_VScrollRect->GetChild(i);
                if (ChildRect->gameObject->m_Name.compare("VerticalScrollBar") == 0)
                {
                    m_VScrollBarRect = ChildRect;
                }
            }
        }

        if (m_HScrollRect != nullptr)
        {
            int cnt = m_HScrollRect->GetChildCount();
            for (int i = 0; i < cnt; i++)
            {
                RectTransform* ChildRect = m_HScrollRect->GetChild(i);
                if (ChildRect->gameObject->m_Name.compare("HorizontalScrollBar") == 0)
                {
                    m_HScrollBarRect = ChildRect;
                }
            }
        }

        CalcScrollMovableRange();
        CalcContentMovableRange();
    }
}

void ViewBox::Update()
{
    if (m_ContentRect == nullptr) return;

    if (m_isDown)
    {
        Vector2 testnormal;

        Vector2 gap;
        Vector2 childLT, childRB, rectLT, rectRB;

        Vector2 pos = m_Rect->GetScreenPosition();
        Vector2 childPos = m_ContentRect->GetScreenPosition();

        test = NormalizePosition(m_ContentRect->GetPosition(), m_ContentMinRange, m_ContentMaxRange);

        childLT.x = childPos.x - (m_ContentRect->m_Size.x * 0.5);   //contentbox좌측변 좌표
        childLT.y = childPos.y - (m_ContentRect->m_Size.y * 0.5);   //contentbox상측변 좌표

        childRB.x = childPos.x + (m_ContentRect->m_Size.x * 0.5);   //contentbox우측변 좌표
        childRB.y = childPos.y + (m_ContentRect->m_Size.y * 0.5);   //contentbox하측변 좌표

        rectLT.x = pos.x - (m_Rect->m_Size.x * 0.5);      //viewbox좌측변 좌표
        rectLT.y = pos.y - (m_Rect->m_Size.y * 0.5);      //viewbox상측변 좌표

        rectRB.x = pos.x + (m_Rect->m_Size.x * 0.5);      //viewbox우측변 좌표
        rectRB.y = pos.y + (m_Rect->m_Size.y * 0.5);      //viewbox하측변 좌표

        //콘텐츠박스의 좌/우측변이 뷰박스의 좌/우측변의 밖에 있으면 x축이동 가능
        if (childLT.x < rectLT.x && childRB.x > rectRB.x)
        {
            Vector2 temppos = m_ContentRect->GetPosition();
            temppos.x = temppos.x + (Input::MousePosition.x - m_MousePrePos.x);
            m_ContentRect->SetPosition(temppos);
        }
        //콘텐츠박스의 좌/우측변이 뷰박스의 좌/우측변과 같으면 해당 방향으로의 이동만 제한
        else if (childLT.x == rectLT.x)
        {
            if (Input::MousePosition.x < m_MousePrePos.x)
            {
                Vector2 temppos = m_ContentRect->GetPosition();
                temppos.x = temppos.x + (Input::MousePosition.x - m_MousePrePos.x);
                m_ContentRect->SetPosition(temppos);
            }
        }
        else if (childRB.x == rectRB.x)
        {
            if (Input::MousePosition.x > m_MousePrePos.x)
            {
                Vector2 temppos = m_ContentRect->GetPosition();
                temppos.x = temppos.x + (Input::MousePosition.x - m_MousePrePos.x);
                m_ContentRect->SetPosition(temppos);
            }
        }

        //콘텐츠박스의 좌측변이 뷰박스의 좌측변의 안에 있으면 변 위치 맞춤
        if (childLT.x > rectLT.x)
        {
            gap.x = childLT.x - rectLT.x;

            Vector2 temppos = m_ContentRect->GetPosition();
            temppos.x -= gap.x;
            m_ContentRect->SetPosition(temppos);
        }
        //콘텐츠박스의 좌측변이 뷰박스의 좌측변의 안에 있으면 변 위치 맞춤
        if (childRB.x < rectRB.x)
        {
            gap.x = childRB.x - rectRB.x;

            Vector2 temppos = m_ContentRect->GetPosition();
            temppos.x -= gap.x;
            m_ContentRect->SetPosition(temppos);
        }

        //y축도 똑같이 해줌
        if (childLT.y < rectLT.y && childRB.y > rectRB.y)
        {
            Vector2 temppos = m_ContentRect->GetPosition();
            temppos.y = temppos.y + (Input::MousePosition.y - m_MousePrePos.y);
            m_ContentRect->SetPosition(temppos);
        }
        else if (childLT.y == rectLT.y)
        {
            if (Input::MousePosition.y < m_MousePrePos.y)
            {
                Vector2 temppos = m_ContentRect->GetPosition();
                temppos.y = temppos.y + (Input::MousePosition.y - m_MousePrePos.y);
                m_ContentRect->SetPosition(temppos);
            }
        }
        else if (childRB.y == rectRB.y)
        {
            if (Input::MousePosition.y > m_MousePrePos.y)
            {
                Vector2 temppos = m_ContentRect->GetPosition();
                temppos.y = temppos.y + (Input::MousePosition.y - m_MousePrePos.y);
                m_ContentRect->SetPosition(temppos);
            }
        }

        if (childLT.y > rectLT.y)
        {
            gap.y = childLT.y - rectLT.y;

            Vector2 temppos = m_ContentRect->GetPosition();
            temppos.y -= gap.y;
            m_ContentRect->SetPosition(temppos);
        }
        if (childRB.y < rectRB.y)
        {
            gap.y = childRB.y - rectRB.y;

            Vector2 temppos = m_ContentRect->GetPosition();
            temppos.y -= gap.y;
            m_ContentRect->SetPosition(temppos);
        }

        m_MousePrePos = Input::MousePosition;
    }
}

//스크롤바의 가동 영역을 구함
void ViewBox::CalcScrollMovableRange()
{
    //현재 스크롤바 높이/길이 계산
    //스크롤의 상하/좌우 끝 좌표에서 스크롤바 높이/길이 절반만큼 제외 = 가동영역
    if (m_VScrollBarRect != nullptr)
    {
        m_ScrollBarMaxRange.y = (m_VScrollRect->m_Size.y - m_VScrollBarRect->m_Size.y) * 0.5;
        m_ScrollBarMinRange.y = -(m_VScrollRect->m_Size.y - m_VScrollBarRect->m_Size.y) * 0.5;
    }

    if (m_HScrollBarRect != nullptr)
    {
        m_ScrollBarMaxRange.x = (m_HScrollRect->m_Size.x - m_HScrollBarRect->m_Size.x) * 0.5;
        m_ScrollBarMinRange.x = -(m_HScrollRect->m_Size.x - m_HScrollBarRect->m_Size.x) * 0.5;
    }
}

//콘텐츠박스의 가동 영역을 구함
void ViewBox::CalcContentMovableRange()
{
    //뷰박스와 콘텐츠박스의 높이, 길이 계산
    //높이와 길이를 모두 절반으로 나눠서 그 차이를 구하고
    //뷰박스의 위치 기준 +- 구한 차이값이 가동 영역
    //위에 만들어놓은 콘텐츠박스 이동 막는것도 이거 사용하도록 개편
    if (m_ContentRect != nullptr)
    {
        m_ContentMaxRange.x = (m_ContentRect->m_Size.x - m_Rect->m_Size.x) * 0.5;
        m_ContentMaxRange.y = (m_ContentRect->m_Size.y - m_Rect->m_Size.y) * 0.5;
        m_ContentMinRange.x = -(m_ContentRect->m_Size.x - m_Rect->m_Size.x) * 0.5;
        m_ContentMinRange.y = -(m_ContentRect->m_Size.y - m_Rect->m_Size.y) * 0.5;
    }
}

//가동 영역 내 현재 위치를 0~1사이의 값으로 변환함()
Vector2 ViewBox::NormalizePosition(Vector2 p_CurrentPos, Vector2 p_MinPos, Vector2 p_MaxPos)
{
    Vector2 normal;

    normal.x = p_CurrentPos.x / (p_MaxPos.x - p_MinPos.x) + 0.5;
    normal.y = p_CurrentPos.y / (p_MaxPos.y - p_MinPos.y) + 0.5;

    return normal;
}

//콘텐츠박스에서 가동 영역을 구하고 해당 영역 내에서의 위치값을 0~1 사이의 값으로 변환
//해당 값을 스크바가 받아서 본인의 가동 영역에 적용
//반대도 마찬가지
//관련 값은 뷰박스가 다 관리하게 만들면 될듯
//필요한것> 가동영역 구하는 함수, 가동 영역에 따른 비율 구하는 함수

//뷰박스의 크기와 콘텐츠박스의 크기의 차이에 따라 스크롤바 크기 조정(0.1~1)
//스크롤바 크기가 1이되면 스크롤 비활성화

//콘텐츠박스에 가동 최고점에 도달하면 사이즈 늘리고 늘린 길이의 절반만큼 내리는 기능 추가

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
    Vector2 childPos = m_ContentRect->GetScreenPosition();

    childLT.x = childPos.x - (m_ContentRect->m_Size.x * 0.5);   //contentbox좌측변 좌표
    childLT.y = childPos.y - (m_ContentRect->m_Size.y * 0.5);   //contentbox상측변 좌표

    childRB.x = childPos.x + (m_ContentRect->m_Size.x * 0.5);   //contentbox우측변 좌표
    childRB.y = childPos.y + (m_ContentRect->m_Size.y * 0.5);   //contentbox하측변 좌표

    rectLT.x = pos.x - (m_Rect->m_Size.x * 0.5);      //viewbox좌측변 좌표
    rectLT.y = pos.y - (m_Rect->m_Size.y * 0.5);      //viewbox상측변 좌표

    rectRB.x = pos.x + (m_Rect->m_Size.x * 0.5);      //viewbox우측변 좌표
    rectRB.y = pos.y + (m_Rect->m_Size.y * 0.5);      //viewbox하측변 좌표


    if (childLT.y < rectLT.y)
    {
        Vector2 temppos = m_ContentRect->GetPosition();
        temppos.y += 5;
        m_ContentRect->SetPosition(temppos);
    }

    if (childLT.y > rectLT.y)
    {
        gap.y = childLT.y - rectLT.y;

        Vector2 temppos = m_ContentRect->GetPosition();
        temppos.y -= gap.y;
        m_ContentRect->SetPosition(temppos);
    }
}

void ViewBox::OnWheelDown()
{
    Vector2 gap;
    Vector2 childLT, childRB, rectLT, rectRB;

    Vector2 pos = m_Rect->GetScreenPosition();
    Vector2 childPos = m_ContentRect->GetScreenPosition();

    childLT.x = childPos.x - (m_ContentRect->m_Size.x * 0.5);   //contentbox좌측변 좌표
    childLT.y = childPos.y - (m_ContentRect->m_Size.y * 0.5);   //contentbox상측변 좌표

    childRB.x = childPos.x + (m_ContentRect->m_Size.x * 0.5);   //contentbox우측변 좌표
    childRB.y = childPos.y + (m_ContentRect->m_Size.y * 0.5);   //contentbox하측변 좌표

    rectLT.x = pos.x - (m_Rect->m_Size.x * 0.5);      //viewbox좌측변 좌표
    rectLT.y = pos.y - (m_Rect->m_Size.y * 0.5);      //viewbox상측변 좌표

    rectRB.x = pos.x + (m_Rect->m_Size.x * 0.5);      //viewbox우측변 좌표
    rectRB.y = pos.y + (m_Rect->m_Size.y * 0.5);      //viewbox하측변 좌표

    if (childRB.y > rectRB.y)
    {
        Vector2 temppos = m_ContentRect->GetPosition();
        temppos.y -= 5;
        m_ContentRect->SetPosition(temppos);
    }

    if (childRB.y < rectRB.y)
    {
        gap.y = childRB.y - rectRB.y;

        Vector2 temppos = m_ContentRect->GetPosition();
        temppos.y -= gap.y;
        m_ContentRect->SetPosition(temppos);
    }
}

//드래그로 이동, 마우스 휠로 이동 완료
//스크롤바 추가하기, 뷰박스 범위 넘어간 이미지 자르기 해야함5