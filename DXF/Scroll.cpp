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
        //viewbox�� ������ ��ǥ ������
        point1.x = parentrect->GetPosition().x + (parentrect->m_Size.x * 0.5);

        pos = rect->GetScreenPosition();
        //Scroll�� ������ ��ǥ ������
        point2.x = pos.x + (rect->m_Size.x * 0.5);

        //viewbox�� Scroll�� ���� �� ������ �Ÿ� ���
        gap.x = point2.x - point1.x;

        //��ڽ��� ���� ���� ��ũ���� ��ġ�ϵ��� ����
        rect->SetPosition(Vector2(rect->GetPosition().x - gap.x, 0));

        //��ڽ��� ��ũ���� ���� �����ϰ� ����
        rect->m_Size.y = parentrect->m_Size.y;
    }
    else
    {
        //viewbox�� ������ ��ǥ ������
        point1.y = parentrect->GetPosition().y + (parentrect->m_Size.y * 0.5);

        pos = rect->GetScreenPosition();
        //Scroll�� ������ ��ǥ ������
        point2.y = pos.y + (rect->m_Size.y * 0.5);

        //viewbox�� Scroll�� ������ ������ �Ÿ� ���
        gap.y = point2.y - point1.y;

        //��ڽ��� �������� ��ũ���� ��ġ�ϵ��� ����
        rect->SetPosition(Vector2(-7.5f, rect->GetPosition().y - gap.y));

        //��ũ���� ���� ����
        rect->m_Size.x = parentrect->m_Size.x - 15;
    }
}