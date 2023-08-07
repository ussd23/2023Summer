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

    //시작할때 스크롤영역을 뷰박스의 우측에 맞춤
    RectTransform* rect = GetComponentFromObject(gameObject, RectTransform);
    if (rect == nullptr) return;

    RectTransform* parentrect = rect->GetParent();
    if (parentrect == nullptr) return;

    Vector2 gap, point1, point2, pos;

    //viewbox의 우측변 좌표 구함
    point1.x = parentrect->position.x + (parentrect->size.x * 0.5);

    pos = rect->GetScreenPosition();
    //Scroll의 우측변 좌표 구함
    point2.x = pos.x + (rect->size.x * 0.5);

    //viewbox와 Scroll의 우측변 사이의 거리 구함
    gap.x = point2.x - point1.x;

    //우측변 위치 맞춰줌
    rect->position.x = rect->position.x - gap.x;

    //스크롤 영역의 높이를 뷰박스에 맞추고 y좌표를 0으로 설정
    rect->size.y = parentrect->size.y;
    rect->position.y = 0;
}