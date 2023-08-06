#include "DXHeader.h"
#include "Global.h"
#include "Functions.h"
#include "GameObject.h"
#include "ComponentHeader.h"

LPDIRECT3D9	DXFGame::m_pD3D;
LPDIRECT3DDEVICE9 DXFGame::m_pd3dDevice;
D3DMATERIAL9 DXFGame::m_defaultMaterial;
IDirect3DBaseTexture9* DXFGame::m_defaultTexture;
LPDIRECT3DVERTEXBUFFER9 DXFGame::m_pVB;
LPD3DXSPRITE DXFGame::m_pSprite;
Matrix16 DXFGame::m_ViewMatrix;
Matrix16 DXFGame::m_ProjMatrix;

void DXFGame::ComponentRegister()
{
    ComponentManager::RegisterComponent<Animator>(typeid(Animator).name());
    ComponentManager::RegisterComponent<BoxCollider>(typeid(BoxCollider).name());
    ComponentManager::RegisterComponent<Camera>(typeid(Camera).name());
    ComponentManager::RegisterComponent<MeshRenderer>(typeid(MeshRenderer).name());
    ComponentManager::RegisterComponent<MouseFunction>(typeid(MouseFunction).name());
    ComponentManager::RegisterComponent<RectTransform>(typeid(RectTransform).name());
    ComponentManager::RegisterComponent<SphereCollider>(typeid(SphereCollider).name());
    ComponentManager::RegisterComponent<SpriteRenderer>(typeid(SpriteRenderer).name());
    ComponentManager::RegisterComponent<TextRenderer>(typeid(TextRenderer).name());
    ComponentManager::RegisterComponent<Transform>(typeid(Transform).name());
    ComponentManager::RegisterComponent<VerticeRenderer>(typeid(VerticeRenderer).name());
}

void DXFGame::Start()
{
    for (int i = 0; i < Var::NewComponents.size(); ++i)
    {
        Var::NewComponents[i]->Awake();
    }
    for (int i = 0; i < Var::NewComponents.size(); ++i)
    {
        Var::NewComponents[i]->Start();
    }
    Var::NewComponents.clear();
}

void DXFGame::Update()
{
    if (Var::RootObject != nullptr) Var::RootObject->PreUpdate();
    if (Var::RootRectObject != nullptr) Var::RootRectObject->PreUpdate();

    if (Var::RootObject != nullptr) Var::RootObject->Update();
    if (Var::RootRectObject != nullptr) Var::RootRectObject->Update();

    if (Var::RootObject != nullptr) Var::RootObject->LateUpdate();
    if (Var::RootRectObject != nullptr) Var::RootRectObject->LateUpdate();
}