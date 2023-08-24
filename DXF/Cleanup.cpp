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
    UnregisterClass("DXF", m_WndClass.hInstance);

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

    if (m_pd3dDevice != NULL)
        m_pd3dDevice->Release();

    if (m_pD3D != NULL)
        m_pD3D->Release();

    if (m_DefaultTexture != NULL)
        m_DefaultTexture->Release();

    if (m_pVB != NULL)
        m_pVB->Release();

    delete Var::Frustum;
    Var::Frustum = nullptr;
}