#include "ComponentHeader.h"

void ContentBox::Start()
{
    //�����Ҷ� �������ڽ��� �»�� �������� ��ڽ��� �»�� �������� ����
    RectTransform* rect = GetComponentFromObject(gameObject, RectTransform);
    if (rect == nullptr) return;

    RectTransform* parentrect = rect->GetParent();
    if (parentrect == nullptr) return;

    Vector2 gap, point1, point2, pos;

    //viewbox�� �»�� ������ ��ġ ����
    Vector2 position = parentrect->GetPosition();

    point1.x = position.x - (parentrect->m_Size.x * 0.5);
    point1.y = position.y - (parentrect->m_Size.y * 0.5);

    pos = rect->GetScreenPosition();
    //contentbox�� �»�� ������ ��ġ ����
    point2.x = pos.x - (rect->m_Size.x * 0.5);
    point2.y = pos.y - (rect->m_Size.y * 0.5);

    //viewbox�� contentbox�� �»�� ������ ������ �Ÿ� ����
    gap.x = point2.x - point1.x;
    gap.y = point2.y - point1.y;

    //������ ��ġ ������
    position = rect->GetPosition();
    position -= gap;
    rect->SetPosition(position);
}