#include "ComponentHeader.h"

void Scroll::Start()
{
    RectTransform* rect = GetComponentFromObject(gameObject, RectTransform);
    if (rect == nullptr) return;

    RectTransform* parentrect = rect->GetParent();
    if (parentrect == nullptr) return;

    Vector2 gap, point1, point2, pos;

    //viewbox의 우측끝 좌표 가져옴
    point1.x = parentrect->GetPosition().x + (parentrect->m_Size.x * 0.5);

    pos = rect->GetScreenPosition();
    //Scroll의 우측끝 좌표 가져옴
    point2.x = pos.x + (rect->m_Size.x * 0.5);

    //viewbox와 Scroll의 우측 끝 사이의 거리 계산
    gap.x = point2.x - point1.x;

    //뷰박스의 우측 끝에 스크롤이 위치하도록 설정
    Vector2 temp = rect->GetPosition();

    temp.x = temp.x - gap.x;
    rect->SetPosition(temp);

    //뷰박스와 스크롤의 높이 동일하게 설정
    rect->m_Size.y = parentrect->m_Size.y;
    rect->GetPosition().y = 0;
}