#include "ComponentHeader.h"

Button::Button(string _texturename, DWORD _color, Vector2 _rectsize, Vector2 _rectindex)
{
    spr = new SpriteRenderer(_texturename, _color, _rectsize, _rectindex);
    mouse = new MouseFunction();
}

void Button::Start()
{
    AddComponentToObject(gameObject, spr);
    AddComponentToObject(gameObject, mouse);
}

void Button::OnMouseDown()
{
    if (spr == nullptr) return;

    spr->color = 0xff808080;
}

void Button::OnMouseUp()
{
    if (spr == nullptr) return;

    spr->color = 0xffffffff;
}
