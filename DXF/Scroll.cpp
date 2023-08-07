#include "ComponentHeader.h"

Scroll::Scroll()
{
    spr = new SpriteRenderer("ScrollArea.png", 0xffffffff, Vector2(1, 1), Vector2(0, 0));
    mouse = new MouseFunction();
}

Scroll::Scroll(Vector2 _rectsize, Vector2 _rectindex)
{
    spr = new SpriteRenderer("ScrollArea.png", 0xffffffff, _rectsize, _rectindex);
    mouse = new MouseFunction();
}

Scroll::Scroll(DWORD _color, Vector2 _rectsize, Vector2 _rectindex)
{
    spr = new SpriteRenderer("ScrollArea.png", _color, _rectsize, _rectindex);
    mouse = new MouseFunction();
}

void Scroll::Start()
{
    AddComponentToObject(gameObject, spr);
    AddComponentToObject(gameObject, mouse);

    //�����Ҷ� ��ũ�ѿ����� ��ڽ��� ������ ����
    RectTransform* rect = GetComponentFromObject(gameObject, RectTransform);
    if (rect == nullptr) return;

    RectTransform* parentrect = rect->GetParent();
    if (parentrect == nullptr) return;

    Vector2 gap, point1, point2, pos;

    //viewbox�� ������ ��ǥ ����
    point1.x = parentrect->position.x + (parentrect->size.x * 0.5);

    pos = rect->GetScreenPosition();
    //Scroll�� ������ ��ǥ ����
    point2.x = pos.x + (rect->size.x * 0.5);

    //viewbox�� Scroll�� ������ ������ �Ÿ� ����
    gap.x = point2.x - point1.x;

    //������ ��ġ ������
    rect->position.x = rect->position.x - gap.x;

    //��ũ�� ������ ���̸� ��ڽ��� ���߰� y��ǥ�� 0���� ����
    rect->size.y = parentrect->size.y;
    rect->position.y = 0;
}