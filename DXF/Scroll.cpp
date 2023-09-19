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