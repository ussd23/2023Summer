#include "ComponentHeader.h"

Scroll::Scroll(bool p_IsVertical)
{
    m_IsVertical = p_IsVertical;
}

void Scroll::Awake()
{
    RectTransform* rect = GetComponentFromObject(gameObject, RectTransform);
    if (rect == nullptr) return;

    RectTransform* parentrect = rect->GetParent();
    if (parentrect == nullptr) return;

    m_ScrollBarRect = rect->GetChild(0);
    if (m_ScrollBarRect == nullptr) return;

    m_ParentView = GetComponentFromObject(rect->GetParent()->gameObject, ViewBox);
    if (m_ParentView == nullptr) return;

    if (m_IsVertical)
    {
        rect->m_Size.y = parentrect->m_Size.y;
    }
    else
    {
        rect->m_Size.x = parentrect->m_Size.x - 15;
    }
}

void Scroll::Start()
{
    AdjustPosition();
}

void Scroll::OnMouseDown()
{
    //스크롤바 위치와 클릭 위치에 따라 방향 결정하고 스크롤바 이동
    //단 스크롤바 이동시 고정치 * 스크롤바 크기만큼 이동
    RectTransform* rect = GetComponentFromObject(gameObject, RectTransform);
    if (rect == nullptr) return;

    m_isDown = true;
    m_ClickTime = GetTickCount64();

    Vector2 barPos = m_ScrollBarRect->GetPosition();
    Vector2 barScreenPos = m_ScrollBarRect->GetScreenPosition();

    Vector2 percent;
    percent.x = m_ScrollBarRect->m_Size.x / rect->m_Size.x;
    percent.y = m_ScrollBarRect->m_Size.y / rect->m_Size.y;


    if (m_IsVertical)
    {
        if (barScreenPos.y > Input::MousePosition.y)
        {
            barPos.y -= 15 * percent.y;
        }
        else
        {
            barPos.y += 15 * percent.y;
        }
    }
    else
    {
        if (barScreenPos.x > Input::MousePosition.x)
        {
            barPos.x -= 15 * percent.x;
        }
        else
        {
            barPos.x += 15 * percent.x;
        }
    }
    m_ScrollBarRect->SetPosition(barPos);
    m_ParentView->UpdateContentBox();
}

void Scroll::OnMouseHold()
{
    //스크롤바 위치와 마우스 위치에 따라 방향 결정하고 스크롤바 이동
    //단 스크롤바 이동시 고정치 * 스크롤바 크기만큼의 속도로 이동
    RectTransform* rect = GetComponentFromObject(gameObject, RectTransform);
    if (rect == nullptr) return;

    Vector2 barPos = m_ScrollBarRect->GetPosition();
    Vector2 barScreenPos = m_ScrollBarRect->GetScreenPosition();

    Vector2 percent;
    percent.x = m_ScrollBarRect->m_Size.x / rect->m_Size.x;
    percent.y = m_ScrollBarRect->m_Size.y / rect->m_Size.y;

    if (m_isDown)
    {
        if (GetTickCount64() > m_ClickTime + 200)
        {
            if (m_IsVertical)
            {
                if (barScreenPos.y > Input::MousePosition.y)
                {
                    barPos.y -= 10 * percent.y;
                }
                else
                {
                    barPos.y += 10 * percent.y;
                }
            }
            else
            {
                if (barScreenPos.x > Input::MousePosition.x)
                {
                    barPos.x -= 10 * percent.x;
                }
                else
                {
                    barPos.x += 10 * percent.x;
                }
            }
            m_ScrollBarRect->SetPosition(barPos);
            m_ParentView->UpdateContentBox();
        }
    }
}

void Scroll::OnMouseUp()
{
    m_isDown = false;
}

void Scroll::OnMouseExit()
{
    m_isDown = false;
}

bool Scroll::GetIsVertical()
{
    return m_IsVertical;
}

void Scroll::AdjustPosition()
{
    RectTransform* rect = GetComponentFromObject(gameObject, RectTransform);
    if (rect == nullptr) return;

    RectTransform* parentrect = rect->GetParent();
    if (parentrect == nullptr) return;

    Vector2 gap, point1, point2, pos;

    if (m_IsVertical)
    {
        //viewbox의 우측끝 좌표 가져옴
        point1.x = parentrect->GetPosition().x + (parentrect->m_Size.x * 0.5);

        pos = rect->GetScreenPosition();
        //Scroll의 우측끝 좌표 가져옴
        point2.x = pos.x + (rect->m_Size.x * 0.5);

        //viewbox와 Scroll의 우측 끝 사이의 거리 계산
        gap.x = point2.x - point1.x;

        //뷰박스의 우측 끝에 스크롤이 위치하도록 설정
        rect->SetPosition(Vector2(rect->GetPosition().x - gap.x, 0));

        //뷰박스와 스크롤의 높이 동일하게 설정
        rect->m_Size.y = parentrect->m_Size.y;
    }
    else
    {
        //viewbox의 하측끝 좌표 가져옴
        point1.y = parentrect->GetPosition().y + (parentrect->m_Size.y * 0.5);

        pos = rect->GetScreenPosition();
        //Scroll의 하측끝 좌표 가져옴
        point2.y = pos.y + (rect->m_Size.y * 0.5);

        //viewbox와 Scroll의 하측끝 사이의 거리 계산
        gap.y = point2.y - point1.y;

        //뷰박스의 하측끝에 스크롤이 위치하도록 설정
        rect->SetPosition(Vector2(-7.5f, rect->GetPosition().y - gap.y));

        //스크롤의 길이 조정
        rect->m_Size.x = parentrect->m_Size.x - 15;
    }
}