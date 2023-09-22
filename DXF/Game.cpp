#include "DXHeader.h"
#include "Global.h"
#include "Functions.h"
#include "GameObject.h"
#include "ComponentHeader.h"

HWND DXFGame::m_hWnd;
HWND DXFGame::m_hDlg;
WNDCLASSEX DXFGame::m_WndClass;
MSG DXFGame::m_Msg;
string DXFGame::m_Title = "DXF Sample";
Vector2 DXFGame::m_Resolution = Vector2(800, 600);
float DXFGame::m_RenderDistance = 1000.0f;
bool DXFGame::m_VSync = true;
LPDIRECT3D9	DXFGame::m_pD3D;
LPDIRECT3DDEVICE9 DXFGame::m_pd3dDevice;
D3DPRESENT_PARAMETERS DXFGame::m_d3dpp;
D3DMATERIAL9 DXFGame::m_DefaultMaterial;
IDirect3DBaseTexture9* DXFGame::m_DefaultTexture;
LPDIRECT3DVERTEXBUFFER9 DXFGame::m_pVB;
LPD3DXSPRITE DXFGame::m_pSprite;
Matrix16 DXFGame::m_ViewMatrix;
Matrix16 DXFGame::m_ProjMatrix;
LPDIRECT3DSURFACE9 DXFGame::m_pStencilSurface;
bool DXFGame::m_DebugMode = false;
HFONT DXFGame::m_hFont;
int DXFGame::m_HTab = 0;
int DXFGame::m_ITab = 0;
bool DXFGame::m_DebugUpdate = false;
float DXFGame::m_DebugUpdateTerm = 0;
float DXFGame::m_HandleUpdateTerm = 0;

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
    ComponentRegist(Scroll);
    ComponentRegist(ScrollBar);
}

void DXFGame::Start()
{
    if (Time::paused) return;

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
    if (m_DebugMode && GetInputBuffer(Key, 'P'))
    {
        Time::paused = !Time::paused;
    }

    if (Time::paused) return;

    if (Var::RootObject != nullptr) Var::RootObject->PreUpdate();
    if (Var::RootRectObject != nullptr) Var::RootRectObject->PreUpdate();

    if (Var::RootObject != nullptr) Var::RootObject->Update();
    if (Var::RootRectObject != nullptr) Var::RootRectObject->Update();

    MouseFunction::UniqueCheck();

    if (Var::RootObject != nullptr) Var::RootObject->LateUpdate();
    if (Var::RootRectObject != nullptr) Var::RootRectObject->LateUpdate();

    if (m_DebugMode) DebugCheck();
}

void DXFGame::Message()
{
    Vector2 resolution = m_Resolution;

    if (PeekMessage(&m_Msg, NULL, 0U, 0U, PM_REMOVE))
    {
        if (!(m_Msg.message == WM_KEYDOWN && m_Msg.lParam & (1 << 30)) &&
            !(m_Msg.hwnd == m_hDlg && m_Msg.message == WM_MOUSEMOVE))
        {
            TranslateMessage(&m_Msg);
            DispatchMessage(&m_Msg);
        }
    }

    if (resolution != m_Resolution)
    {
        if (m_DefaultTexture != NULL) m_DefaultTexture->Release();
        if (m_pVB != NULL)
        {
            m_pVB->Release();
            m_pVB = NULL;
        }

        if (m_pSprite != nullptr) m_pSprite->OnLostDevice();
        FontManager::GetInstance()->OnLost();

        m_d3dpp.BackBufferWidth = m_Resolution.x;
        m_d3dpp.BackBufferHeight = m_Resolution.y;

        m_pd3dDevice->Reset(&m_d3dpp);

        m_pd3dDevice->GetMaterial(&m_DefaultMaterial);
        m_pd3dDevice->GetTexture(0, &m_DefaultTexture);
        m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
        m_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
        m_pd3dDevice->SetRenderState(D3DRS_COLORVERTEX, TRUE);
        m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

        if (m_pSprite != nullptr) m_pSprite->OnResetDevice();
        FontManager::GetInstance()->OnReset();
        MeshManager::GetInstance()->OnReset();
    }

    if (m_DebugMode)
    {
        stringstream ss;
        ss << "[Debug Mode";
        if (Time::paused) ss << " (Paused)";
        ss << fixed << setprecision(2) << " / " << Time::framePerSec << " fps";
        if (m_VSync) ss << " (VSync Enabled)";
        ss << "] " << m_Title;

        SetWindowText(m_hWnd, ss.str().c_str());
    }
}