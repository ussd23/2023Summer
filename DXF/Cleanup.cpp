#include "DXHeader.h"
#include "Functions.h"
#include "Global.h"
#include "MeshRenderer.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include "FontManager.h"
#include "GameObject.h"

VOID DXFGame::Cleanup()
{
    TextureManager::GetInstance()->Cleanup();
    MeshManager::GetInstance()->Cleanup();
    FontManager::GetInstance()->Cleanup();

    if (g_RootObject != nullptr)
    {
        GameObject::Destroy(g_RootObject);
    }

    if (g_RootRectObject != nullptr)
    {
        GameObject::Destroy(g_RootRectObject);
    }

    GameObject::SafeDestroy();

    if (g_pd3dDevice != NULL)
        g_pd3dDevice->Release();

    if (g_pD3D != NULL)
        g_pD3D->Release();

    if (g_defaultTexture != NULL)
        g_defaultTexture->Release();

    if (g_pVB != NULL)
        g_pVB->Release();
}