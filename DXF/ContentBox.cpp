#include "ComponentHeader.h"

ContentBox::ContentBox()
{
    spr = new SpriteRenderer("default.png", 0x20ffffff, Vector2(1, 1), Vector2(0, 0));
    mouse = new MouseFunction();
}

ContentBox::ContentBox(Vector2 _rectsize, Vector2 _rectindex)
{
    spr = new SpriteRenderer("default.png", 0x20ffffff, _rectsize, _rectindex);
    mouse = new MouseFunction();
}

ContentBox::ContentBox(DWORD _color, Vector2 _rectsize, Vector2 _rectindex)
{
    spr = new SpriteRenderer("default.png", _color, _rectsize, _rectindex);
    mouse = new MouseFunction();
}

void ContentBox::Start()
{
    AddComponentToObject(gameObject, spr);
    AddComponentToObject(gameObject, mouse);

    //�����Ҷ� �������ڽ��� �»�� �������� ��ڽ��� �»�� �������� ����
    RectTransform* rect = GetComponentFromObject(gameObject, RectTransform);
    if (rect == nullptr) return;

    RectTransform* parentrect = rect->GetParent();
    if (parentrect == nullptr) return;

    Vector2 gap, point1, point2, pos;

    //viewbox�� �»�� ������ ��ġ ����
    point1.x = parentrect->position.x - (parentrect->size.x * 0.5);
    point1.y = parentrect->position.y - (parentrect->size.y * 0.5);

    pos = rect->GetScreenPosition();
    //contentbox�� �»�� ������ ��ġ ����
    point2.x = pos.x - (rect->size.x * 0.5);
    point2.y = pos.y - (rect->size.y * 0.5);

    //viewbox�� contentbox�� �»�� ������ ������ �Ÿ� ����
    gap.x = point2.x - point1.x;
    gap.y = point2.y - point1.y;

    //������ ��ġ ������
    rect->position.x = rect->position.x - gap.x;
    rect->position.y = rect->position.y - gap.y;
}