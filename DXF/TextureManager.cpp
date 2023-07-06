#include "TextureManager.h"

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(const string& _filepath)
{
    map<string, LPDIRECT3DTEXTURE9>::iterator iter = texturesmap.find(_filepath);
    if (iter != texturesmap.end())
    {
        return iter->second;
    }

    LPDIRECT3DTEXTURE9 texture;

    string path = "resources\\" + _filepath;
    if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, path.c_str(), &texture)))
    {
        path = "..\\resources\\" + _filepath;
        if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, path.c_str(), &texture)))
        {
            path = "..\\..\\resources\\" + _filepath;
            if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, path.c_str(), &texture)))
            {
                MessageBox(NULL, "Could not find texture", "Texture Load Failed", MB_OK);
                return NULL;
            }
        }
    }

    textures.push_back(texture);
    texturesmap.insert(make_pair(_filepath, texture));
    return texture;
}

void TextureManager::Cleanup()
{
    for (int i = 0; i < textures.size(); ++i)
    {
        textures[i]->Release();
    }
}