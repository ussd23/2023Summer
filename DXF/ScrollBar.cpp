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
        //scroll�� ScrollBar�� ���� ����
        rect->m_Size.y = parentrect->m_Size.y * 0.3;
    }
    else
    {
        //scroll�� ScrollBar�� ���� ����
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
        //scrollbar�� x��ǥ 0���� ����
        rect->SetPosition(Vector2(0, 0));
    }
    else
    {
        //scrollbar�� y��ǥ 0���� ����
        rect->SetPosition(Vector2(0, 0));
    }

}