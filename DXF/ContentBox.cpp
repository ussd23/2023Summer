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

    //시작할때 콘텐츠박스의 좌상단 꼭지점을 뷰박스의 좌상단 꼭지점에 맞춤
    RectTransform* rect = GetComponentFromObject(gameObject, RectTransform);
    if (rect == nullptr) return;

    RectTransform* parentrect = rect->GetParent();
    if (parentrect == nullptr) return;

    Vector2 gap, point1, point2, pos;

    //viewbox의 좌상단 꼭지점 위치 구함
    point1.x = parentrect->position.x - (parentrect->size.x * 0.5);
    point1.y = parentrect->position.y - (parentrect->size.y * 0.5);

    pos = rect->GetScreenPosition();
    //contentbox의 좌상단 꼭지점 위치 구함
    point2.x = pos.x - (rect->size.x * 0.5);
    point2.y = pos.y - (rect->size.y * 0.5);

    //viewbox와 contentbox의 좌상단 꼭지점 사이의 거리 구함
    gap.x = point2.x - point1.x;
    gap.y = point2.y - point1.y;

    //꼭지점 위치 맞춰줌
    rect->position.x = rect->position.x - gap.x;
    rect->position.y = rect->position.y - gap.y;
}