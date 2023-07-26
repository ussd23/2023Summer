#include "ComponentHeader.h"

Button::Button(Vector2 _pos, Vector3 _rot, Vector2 _scale, Vector2 _size, string _texturename, DWORD _color, Vector2 _rectsize, Vector2 _rectindex)
{
    rect = new RectTransform(_pos, _rot, _scale, _size);
    spr = new SpriteRenderer(_texturename, _color, _rectsize, _rectindex);
    mouse = new MouseFunction();
}

void Button::InitBtn()
{
    AddComponentToObject(gameObject, rect);
    AddComponentToObject(gameObject, spr);
    AddComponentToObject(gameObject, mouse);
}
