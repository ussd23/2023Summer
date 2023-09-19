#include "ComponentHeader.h"

void ScrollBar::Awake()
{
    RectTransform* rect = GetComponentFromObject(gameObject, RectTransform);
    if (rect == nullptr) return;

    RectTransform* parentrect = rect->GetParent();
    if (parentrect == nullptr) return;

    Scroll* parentscroll = GetComponentFromObject(parentrect->gameObject, Scroll);
    if (parentscroll == nullptr) return;

    if (parentscroll->GetIsVertical())
    {
        //scroll과 ScrollBar의 높이 조정
        rect->m_Size.y = parentrect->m_Size.y * 0.3;
    }
    else
    {
        //scroll과 ScrollBar의 길이 조정
        rect->m_Size.x = parentrect->m_Size.x * 0.3;
    }

}

void ScrollBar::Start()
{
    RectTransform* rect = GetComponentFromObject(gameObject, RectTransform);
    if (rect == nullptr) return;

    RectTransform* parentrect = rect->GetParent();
    if (parentrect == nullptr) return;

    Scroll* parentscroll = GetComponentFromObject(parentrect->gameObject, Scroll);
    if (parentscroll == nullptr) return;

    if (parentscroll->GetIsVertical())
    {
        //scrollbar의 x좌표 0으로 만듦
        rect->SetPosition(Vector2(0, 0));
    }
    else
    {
        //scrollbar의 y좌표 0으로 만듦
        rect->SetPosition(Vector2(0, 0));
    }

}