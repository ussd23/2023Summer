#include "FontManager.h"

LPD3DXFONT FontManager::GetFont(string _fontname, int _size)
{
    stringstream temp;
    temp << "font:" << _fontname << "_size:" << _size;

    string key = temp.str();

    map<string, LPD3DXFONT>::iterator iter = fontsmap.find(key);
    if (iter != fontsmap.end())
    {
        return iter->second;
    }

    LPD3DXFONT font;

    AddFontResource(_fontname.c_str());
    D3DXCreateFont(g_pd3dDevice, -_size, 0, FW_DONTCARE, 1, FALSE, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
        _fontname.c_str(), &font);

    fonts.push_back(font);
    fontsmap.insert(make_pair(key, font));
    return font;
}

void FontManager::Cleanup()
{
    for (int i = 0; i < fonts.size(); ++i)
    {
        fonts[i]->Release();
    }
}