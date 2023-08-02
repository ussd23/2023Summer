#include "DXHeader.h"
#include "Functions.h"
#include "Global.h"
#include "Frustum.h"
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

    if (Var::RootObject != nullptr)
    {
        GameObject::Destroy(Var::RootObject);
    }

    if (Var::RootRectObject != nullptr)
    {
        GameObject::Destroy(Var::RootRectObject);
    }

    GameObject::SafeDestroy();

    if (DXFGame::m_pd3dDevice != NULL)
        DXFGame::m_pd3dDevice->Release();

    if (DXFGame::m_pD3D != NULL)
        DXFGame::m_pD3D->Release();

    if (DXFGame::m_defaultTexture != NULL)
        DXFGame::m_defaultTexture->Release();

    if (DXFGame::m_pVB != NULL)
        DXFGame::m_pVB->Release();

    delete Var::Frustum;
    Var::Frustum = nullptr;
}