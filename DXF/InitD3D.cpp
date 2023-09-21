#include "DXHeader.h"
#include "Global.h"
#include "Transform.h"
#include "RectTransform.h"
#include "Frustum.h"

HRESULT DXFGame::InitD3D(HINSTANCE hInst)
{
    UNREFERENCED_PARAMETER(hInst);
    srand(time(NULL));

    m_WndClass =
    {
        sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
        "DXF", NULL
    };
    RegisterClassEx(&m_WndClass);

    m_hWnd = CreateWindow("DXF", m_Title.c_str(),
        WS_OVERLAPPEDWINDOW, 100, 100, m_Resolution.x + 16, m_Resolution.y + 39,
        NULL, NULL, m_WndClass.hInstance, NULL);

    if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
        return E_FAIL;

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;// D3DFMT_D16;
    //d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
        D3DCREATE_HARDWARE_VERTEXPROCESSING,
        &d3dpp, &m_pd3dDevice)))
    {
        if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
            D3DCREATE_SOFTWARE_VERTEXPROCESSING,
            &d3dpp, &m_pd3dDevice)))
        {
            return E_FAIL;
        }
    }

    ShowWindow(m_hWnd, SW_SHOWDEFAULT);
    UpdateWindow(m_hWnd);

    m_pd3dDevice->GetMaterial(&m_DefaultMaterial);
    m_pd3dDevice->GetTexture(0, &m_DefaultTexture);
    m_pd3dDevice->CreateDepthStencilSurface(800, 600, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, TRUE, &m_pStencilSurface, NULL);

    m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
    m_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
    m_pd3dDevice->SetRenderState(D3DRS_COLORVERTEX, TRUE);
    m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
    m_pd3dDevice->SetRenderState(D3DRS_STENCILREF, 1);

    D3DXCreateSprite(m_pd3dDevice, &m_pSprite);

    Var::Frustum = new Frustum();

    Var::RootObject = new GameObject("RootObject");
    Var::RootTransform = new Transform(Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 0.f), Vector3(1.f, 1.f, 1.f));
    AddComponentToObject(Var::RootObject, Var::RootTransform);

    Var::RootRectObject = new GameObject("RootRectObject");
    Var::RootRectTransform = new RectTransform(Vector2(0.f, 0.f), Vector3(0.f, 0.f, 0.f), Vector2(1.f, 1.f), Vector2(0.f, 0.f));
    AddComponentToObject(Var::RootRectObject, Var::RootRectTransform);

    Var::Objects.push_back(Var::RootObject);
    Var::Objects.push_back(Var::RootRectObject);

    //locale krlocale("Korean");
    //locale::global(krlocale);

    return S_OK;
}