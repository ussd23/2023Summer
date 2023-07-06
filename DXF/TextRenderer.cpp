#include "ComponentHeader.h"

TextRenderer::TextRenderer(GameObject* _gameObject, string _fontname, int _size, string _text)
    : TextRenderer(_gameObject, _fontname, _size, _text, D3DCOLOR(0xffffffff)) {}

TextRenderer::TextRenderer(GameObject* _gameObject, string _fontname, int _size, string _text, D3DCOLOR _color)
    : TextRenderer(_gameObject, _fontname, _size, _text, _color, DT_LEFT | DT_TOP) {}

TextRenderer::TextRenderer(GameObject* _gameObject, string _fontname, int _size, string _text, D3DCOLOR _color, DWORD _format)
{
    gameObject = _gameObject;
    fontname = _fontname;
    size = _size;
    text = _text;
    color = _color;
    format = _format;
}

void TextRenderer::Start()
{
    recttransform = GetComponentFromObject(gameObject, RectTransform);

    font = FontManager::GetInstance()->GetFont(fontname, size);
}

void TextRenderer::Render()
{
    if (recttransform == nullptr) return;
    if (font == NULL) return;

    Vector2 pos = recttransform->GetScreenPosition();
    Vector2 size = recttransform->size;

    RECT rect;
    SetRect(&rect, pos.x - size.x / 2, pos.y - size.y / 2, pos.x + size.x / 2, pos.y + size.y / 2);

    font->DrawTextA(NULL, text.c_str(), -1, &rect, format, color);
}
