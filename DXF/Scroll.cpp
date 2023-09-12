#include "ComponentHeader.h"

void Scroll::Start()
{
    RectTransform* rect = GetComponentFromObject(gameObject, RectTransform);
    if (rect == nullptr) return;

    RectTransform* parentrect = rect->GetParent();
    if (parentrect == nullptr) return;

    Vector2 gap, point1, point2, pos;

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