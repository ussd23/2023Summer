#include "ComponentHeader.h"

void ScrollBar::Start()
{
    m_Rect = GetComponentFromObject(gameObject, RectTransform);
    if (m_Rect == nullptr) return;

    RectTransform* parentrect = m_Rect->GetParent();
    if (parentrect == nullptr) return;

    m_ParentScroll = GetComponentFromObject(parentrect->gameObject, Scroll);
    if (m_ParentScroll == nullptr) return;

    RectTransform* parentparentrect = parentrect->GetParent();
    if (parentparentrect == nullptr) return;

    m_ParentView = GetComponentFromObject(parentparentrect->gameObject, ViewBox);
    if (m_ParentView == nullptr) return;
}

void ScrollBar::Update()
{
    if (m_isDown)
    {
        MoveScrollBar();

        //마우스 위치 저장
        m_MousePrePos = Input::MousePosition;
    }
}

void ScrollBar::MoveScrollBar()
{
    if (m_Rect == nullptr) return;

    Vector2 Pos;

    if (m_ParentScroll->GetIsVertical())
    {
        Pos.x = 0;
        Pos.y = m_Rect->GetPosition().y;
    }
    else
    {
        Pos.x = m_Rect->GetPosition().x;
        Pos.y = 0;
    }

    Vector2 normal = m_ParentView->NormalizePosition(Pos, m_ParentView->GetScrollBarMinRange(), m_ParentView->GetScrollBarMaxRange());

    if (!m_ParentScroll->GetIsVertical())
    {
        //우향 가동 한계에 도달한경우 왼쪽으로만 움직일 수 있게 함
        if (normal.x == 1)
        {
            if (Input::MousePosition.x < m_MousePrePos.x)
            {
                Pos.x = Pos.x + (Input::MousePosition.x - m_MousePrePos.x);
            }
        }
        //좌향 가동 한계에 도달한경우 오른쪽으로만 움직일 수 있게 함
        else if (normal.x == 0)
        {
            if (Input::MousePosition.x > m_MousePrePos.x)
            {
                Pos.x = Pos.x + (Input::MousePosition.x - m_MousePrePos.x);
            }
        }
        //어느쪽도 아니라면 자유롭게 움직일 수 있게 함
        else
        {
            Pos.x = Pos.x + (Input::MousePosition.x - m_MousePrePos.x);
        }

        //조정된 위치로 다시 한번 정규화
        normal = m_ParentView->NormalizePosition(Pos, m_ParentView->GetScrollBarMinRange(), m_ParentView->GetScrollBarMaxRange());

        //조정된 위치가 우향 가동 한계를 넘으면 위치를 한계치로 설정
        if (normal.x > 1)
        {
            normal.x = 1;
        }
        //조정된 위치가 좌향 가동 한계를 넘으면 위치를 한계치로 설정
        else if (normal.x < 0)
        {
            normal.x = 0;
        }
    }
    else
    {
        //하향 가동 한계에 도달한경우 위쪽으로만 움직일 수 있게 함
        if (normal.y == 1)
        {
            if (Input::MousePosition.y < m_MousePrePos.y)
            {
                Pos.y = Pos.y + (Input::MousePosition.y - m_MousePrePos.y);
            }
        }
        //상향 가동 한계에 도달한경우 아래쪽으로만 움직일 수 있게 함
        else if (normal.y == 0)
        {
            if (Input::MousePosition.y > m_MousePrePos.y)
            {
                Pos.y = Pos.y + (Input::MousePosition.y - m_MousePrePos.y);
            }
        }
        //어느쪽도 아니라면 자유롭게 움직일 수 있게 함
        else
        {
            Pos.y = Pos.y + (Input::MousePosition.y - m_MousePrePos.y);
        }

        //조정된 위치로 다시 한번 정규화
        normal = m_ParentView->NormalizePosition(Pos, m_ParentView->GetScrollBarMinRange(), m_ParentView->GetScrollBarMaxRange());

        //조정된 위치가 하향 가동 한계를 넘으면 위치를 한계치로 설정
        if (normal.y > 1)
        {
            normal.y = 1;
        }
        //조정된 위치가 상향 가동 한계를 넘으면 위치를 한계치로 설정
        else if (normal.y < 0)
        {
            normal.y = 0;
        }
    }

    //최종 조정된 위치를 스크롤바에 적용
    Vector2 tempPos = m_ParentView->DisNormalizePosition(normal, m_ParentView->GetScrollBarMinRange(), m_ParentView->GetScrollBarMaxRange());
    m_Rect->SetPosition(tempPos);

    //스크롤바의 위치 변경에 맞춰 콘텐츠박스 위치 조정
    m_ParentView->UpdateContentBox();
}

void ScrollBar::OnMouseDown()
{
    m_isDown = true;
    m_MousePrePos = Input::MousePosition;
}

void ScrollBar::OnMouseUp()
{
    m_isDown = false;
}

void ScrollBar::OnMouseExit()
{
    m_isDown = false;
}
