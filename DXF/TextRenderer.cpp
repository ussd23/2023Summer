#include "ComponentHeader.h"

TextRenderer::TextRenderer(string _fontname, int _size, string _text)
    : TextRenderer(_fontname, _size, _text, D3DCOLOR(0xffffffff)) {}

TextRenderer::TextRenderer(string _fontname, int _size, string _text, D3DCOLOR _color)
    : TextRenderer(_fontname, _size, _text, _color, DT_LEFT | DT_TOP) {}

TextRenderer::TextRenderer(string _fontname, int _size, string _text, D3DCOLOR _color, DWORD _format)
{
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

void TextRenderer::PreRender()
{
    if (recttransform == nullptr) return;
    if (font == NULL) return;

    Vector2 pos = recttransform->GetScreenPosition();
    Vector2 size = recttransform->size;

    SetRect(&rect, pos.x - size.x / 2, pos.y - size.y / 2, pos.x + size.x / 2, pos.y + size.y / 2);

    if (Functions::Inner(rect, g_ScreenRect))
    {
        g_RectTransformRenderList.push_back(this);
    }
}

void TextRenderer::Render()
{
    font->DrawTextA(NULL, text.c_str(), -1, &rect, format, color);
}
