#include "ComponentHeader.h"

Checkbox::Checkbox()
{
    texturename[0] = "CheckBoxOff.png";
    texturename[1] = "CheckBoxOn.png";
    textureindex = 0;

    spr = new SpriteRenderer(texturename[0], Vector2(1, 1), Vector2(0, 0));
    mouse = new MouseFunction();
}

Checkbox::Checkbox(Vector2 _rectsize, Vector2 _rectindex)
{
    texturename[0] = "CheckBoxOff.png";
    texturename[1] = "CheckBoxOn.png";
    textureindex = 0;

    spr = new SpriteRenderer(texturename[0], _rectsize, _rectindex);
    mouse = new MouseFunction();
}

Checkbox::Checkbox(DWORD _color, Vector2 _rectsize, Vector2 _rectindex)
{
    texturename[0] = "CheckBoxOff.png";
    texturename[1] = "CheckBoxOn.png";
    textureindex = 0;

    spr = new SpriteRenderer(texturename[0], _color, _rectsize, _rectindex);
    mouse = new MouseFunction();
}

void Checkbox::Start()
{
    AddComponentToObject(gameObject, spr);
    AddComponentToObject(gameObject, mouse);
}

void Checkbox::OnMouseDown()
{
    if (textureindex == 0) textureindex = 1;
    else textureindex = 0;

    spr->ChangeSprite(texturename[textureindex]);
}
