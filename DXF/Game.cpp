#include "DXHeader.h"
#include "Global.h"
#include "Functions.h"
#include "GameObject.h"
#include "ComponentHeader.h"

HWND DXFGame::m_hWnd;
WNDCLASSEX DXFGame::m_WndClass;
string DXFGame::m_Title = "DXF Sample";
Vector2 DXFGame::m_Resolution = Vector2(800, 600);
float DXFGame::m_RenderDistance = 1000.0f;
LPDIRECT3D9	DXFGame::m_pD3D;
LPDIRECT3DDEVICE9 DXFGame::m_pd3dDevice;
D3DMATERIAL9 DXFGame::m_DefaultMaterial;
IDirect3DBaseTexture9* DXFGame::m_DefaultTexture;
LPDIRECT3DVERTEXBUFFER9 DXFGame::m_pVB;
LPD3DXSPRITE DXFGame::m_pSprite;
Matrix16 DXFGame::m_ViewMatrix;
Matrix16 DXFGame::m_ProjMatrix;

void DXFGame::ComponentRegister()
{
    ComponentRegist(Animator);
    ComponentRegist(BoxCollider);
    ComponentRegist(Button);
    ComponentRegist(Camera);
    ComponentRegist(CheckBox);
    ComponentRegist(ContentBox);
    ComponentRegist(MeshRenderer);
    ComponentRegist(MouseFunction);
    ComponentRegist(RectTransform);
    ComponentRegist(SphereCollider);
    ComponentRegist(SpriteRenderer);
    ComponentRegist(TextRenderer);
    ComponentRegist(Transform);
    ComponentRegist(VerticeRenderer);
    ComponentRegist(ViewBox);
}

void DXFGame::Start()
{
    for (int i = 0; i < Var::NewComponents.size(); ++i)
    {
        Var::NewComponents[i]->Awake();
        Var::WaitComponents.push_back(Var::NewComponents[i]);
    }
    Var::NewComponents.clear();

    list<Component*>::iterator iter = Var::WaitComponents.begin();
    while (iter != Var::WaitComponents.end())
    {
        if ((*iter)->gameObject->isActive())
        {
            (*iter)->Start();
            iter = Var::WaitComponents.erase(iter);
        }
        else ++iter;
    }
}

void DXFGame::Update()
{
    if (Var::RootObject != nullptr) Var::RootObject->PreUpdate();
    if (Var::RootRectObject != nullptr) Var::RootRectObject->PreUpdate();

    if (Var::RootObject != nullptr) Var::RootObject->Update();
    if (Var::RootRectObject != nullptr) Var::RootRectObject->Update();

    MouseFunction::UniqueCheck();

    if (Var::RootObject != nullptr) Var::RootObject->LateUpdate();
    if (Var::RootRectObject != nullptr) Var::RootRectObject->LateUpdate();
}

void DXFGame::Message(MSG* msg)
{
    if (PeekMessage(msg, NULL, 0U, 0U, PM_REMOVE))
    {
        TranslateMessage(msg);
        DispatchMessage(msg);
    }
}