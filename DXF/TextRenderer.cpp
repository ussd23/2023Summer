#include "ComponentHeader.h"

TextRenderer::TextRenderer(string p_FontName, int p_FontSize, string p_Text)
    : TextRenderer(p_FontName, p_FontSize, p_Text, D3DCOLOR(0xffffffff), DT_LEFT | DT_TOP) {}

TextRenderer::TextRenderer(string p_FontName, int p_FontSize, string p_Text, D3DCOLOR p_Color)
    : TextRenderer(p_FontName, p_FontSize, p_Text, p_Color, DT_LEFT | DT_TOP) {}

TextRenderer::TextRenderer(string p_FontName, int p_FontSize, string p_Text, D3DCOLOR p_Color, DWORD p_Format)
{
    m_FontName = p_FontName;
    m_FontSize = p_FontSize;
    m_Text = p_Text;
    m_Color = p_Color;
    m_Format = p_Format;
}

void TextRenderer::Start()
{
    m_RectTransform = GetComponentFromObject(gameObject, RectTransform);

    m_Font = FontManager::GetInstance()->GetFont(m_FontName, m_FontSize);
}

void TextRenderer::PreRender()
{
    if (m_RectTransform == nullptr) return;
    if (m_Font == NULL) return;

    Vector2 pos = m_RectTransform->GetScreenPosition();
    Vector2 size = m_RectTransform->m_Size;

    SetRect(&m_Rect, pos.x - size.x * 0.5f, pos.y - size.y , pos.x + size.x * 0.5f, pos.y + size.y * 0.5f);

    if (Functions::Inner(m_Rect, Var::ScreenRect))
    {
        Var::RectTransformRenderList.push_back(this);
    }
}

void TextRenderer::Render()
{
    m_Font->DrawTextA(NULL, m_Text.c_str(), -1, &m_Rect, m_Format, m_Color);
}
