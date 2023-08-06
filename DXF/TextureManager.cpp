#include "TextureManager.h"

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(const string& p_Path)
{
    map<string, LPDIRECT3DTEXTURE9>::iterator iter = m_TexturesMap.find(p_Path);
    if (iter != m_TexturesMap.end())
    {
        return iter->second;
    }

    LPDIRECT3DTEXTURE9 texture;

    string path = "resources\\" + p_Path;
    if (FAILED(D3DXCreateTextureFromFile(DXFGame::m_pd3dDevice, path.c_str(), &texture)))
    {
        path = "..\\resources\\" + p_Path;
        if (FAILED(D3DXCreateTextureFromFile(DXFGame::m_pd3dDevice, path.c_str(), &texture)))
        {
            path = "..\\..\\resources\\" + p_Path;
            if (FAILED(D3DXCreateTextureFromFile(DXFGame::m_pd3dDevice, path.c_str(), &texture)))
            {
                string text = "Could not find texture: " + p_Path;
                MessageBox(NULL, text.c_str(), "Texture Load Failed", MB_OK);
                return NULL;
            }
        }
    }

    m_Textures.push_back(texture);
    m_TexturesMap.insert(make_pair(p_Path, texture));
    return texture;
}

void TextureManager::Cleanup()
{
    for (int i = 0; i < m_Textures.size(); ++i)
    {
        m_Textures[i]->Release();
    }
}