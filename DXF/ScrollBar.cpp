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
        //scroll�� ������ ��ǥ ������
        point1.x = parentrect->GetPosition().x + (parentrect->m_Size.x * 0.5);

        pos = rect->GetScreenPosition();
        //ScrollBar�� ������ ��ǥ ������
        point2.x = pos.x + (rect->m_Size.x * 0.5);

        //scroll�� ScrollBar�� ���� �� ������ �Ÿ� ���
        gap.x = point2.x - point1.x;

        //scroll�� ���� ���� ��ũ���� ��ġ�ϵ��� ����
        rect->SetPosition(Vector2(rect->GetPosition().x - gap.x, 0));

        //scroll�� ScrollBar�� ���� �����ϰ� ����
        rect->m_Size.y = parentrect->m_Size.y;
    }
    else
    {
        //scroll�� ������ ��ǥ ������
        point1.y = parentrect->GetPosition().y + (parentrect->m_Size.y * 0.5);

        pos = rect->GetScreenPosition();
        //ScrollBar�� ������ ��ǥ ������
        point2.y = pos.y + (rect->m_Size.y * 0.5);

        //scroll�� ScrollBar�� ������ ������ �Ÿ� ���
        gap.y = point2.y - point1.y;

        //scroll�� �������� ��ũ���� ��ġ�ϵ��� ����
        rect->SetPosition(Vector2(-7.5f, rect->GetPosition().y - gap.y));

        //AcrollBar�� ���� ����
        rect->m_Size.x = parentrect->m_Size.x - 15;
    }

}
