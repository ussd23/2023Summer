#include "FontManager.h"

LPD3DXFONT FontManager::GetFont(const string& p_FontName, const int& p_Size)
{
    stringstream temp;
    temp << "font:" << p_FontName << "_size:" << p_Size;

    string key = temp.str();

    map<string, LPD3DXFONT>::iterator iter = m_FontsMap.find(key);
    if (iter != m_FontsMap.end())
    {
        return iter->second;
    }

    LPD3DXFONT font;

    AddFontResource(p_FontName.c_str());
    D3DXCreateFont(DXFGame::m_pd3dDevice, -p_Size, 0, FW_DONTCARE, 1, FALSE, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
        p_FontName.c_str(), &font);

    m_Fonts.push_back(font);
    m_FontsMap.insert(make_pair(key, font));
    return font;
}

void FontManager::Cleanup()
{
    for (int i = 0; i < m_Fonts.size(); ++i)
    {
        m_Fonts[i]->Release();
    }
}