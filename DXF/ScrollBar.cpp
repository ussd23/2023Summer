#include "ComponentHeader.h"

void ScrollBar::Start()
{
    RectTransform* rect = GetComponentFromObject(gameObject, RectTransform);
    if (rect == nullptr) return;

    RectTransform* parentrect = rect->GetParent();
    if (parentrect == nullptr) return;

    Scroll* parentscroll = GetComponentFromObject(parentrect->gameObject, Scroll);
    if (parentscroll == nullptr) return;

    Vector2 gap, point1, point2, pos;

    if (parentscroll->GetIsVertical())
    {
        //scroll의 우측끝 좌표 가져옴
        point1.x = parentrect->GetPosition().x + (parentrect->m_Size.x * 0.5);

        pos = rect->GetScreenPosition();
        //ScrollBar의 우측끝 좌표 가져옴
        point2.x = pos.x + (rect->m_Size.x * 0.5);

        //scroll과 ScrollBar의 우측 끝 사이의 거리 계산
        gap.x = point2.x - point1.x;

        //scroll의 우측 끝에 스크롤이 위치하도록 설정
        rect->SetPosition(Vector2(rect->GetPosition().x - gap.x, 0));

        //scroll과 ScrollBar의 높이 동일하게 설정
        rect->m_Size.y = parentrect->m_Size.y;
    }
    else
    {
        //scroll의 하측끝 좌표 가져옴
        point1.y = parentrect->GetPosition().y + (parentrect->m_Size.y * 0.5);

        pos = rect->GetScreenPosition();
        //ScrollBar의 하측끝 좌표 가져옴
        point2.y = pos.y + (rect->m_Size.y * 0.5);

        //scroll과 ScrollBar의 하측끝 사이의 거리 계산
        gap.y = point2.y - point1.y;

        //scroll의 하측끝에 스크롤이 위치하도록 설정
        rect->SetPosition(Vector2(-7.5f, rect->GetPosition().y - gap.y));

        //AcrollBar의 길이 조정
        rect->m_Size.x = parentrect->m_Size.x - 15;
    }

}
