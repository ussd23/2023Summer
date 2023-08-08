#include "ComponentHeader.h"

void ContentBox::Start()
{
    //시작할때 콘텐츠박스의 좌상단 꼭지점을 뷰박스의 좌상단 꼭지점에 맞춤
    RectTransform* rect = GetComponentFromObject(gameObject, RectTransform);
    if (rect == nullptr) return;

    RectTransform* parentrect = rect->GetParent();
    if (parentrect == nullptr) return;

    Vector2 gap, point1, point2, pos;

    //viewbox의 좌상단 꼭지점 위치 구함
    Vector2 position = parentrect->GetPosition();

    point1.x = position.x - (parentrect->m_Size.x * 0.5);
    point1.y = position.y - (parentrect->m_Size.y * 0.5);

    pos = rect->GetScreenPosition();
    //contentbox의 좌상단 꼭지점 위치 구함
    point2.x = pos.x - (rect->m_Size.x * 0.5);
    point2.y = pos.y - (rect->m_Size.y * 0.5);

    //viewbox와 contentbox의 좌상단 꼭지점 사이의 거리 구함
    gap.x = point2.x - point1.x;
    gap.y = point2.y - point1.y;

    //꼭지점 위치 맞춰줌
    position = rect->GetPosition();
    position -= gap;
    rect->SetPosition(position);
}