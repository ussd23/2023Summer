#include "resource.h"
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

    if (m_DebugMode && !IsWindow(m_hDlg)) {
        m_hDlg = CreateDialog(hInst, MAKEINTRESOURCE(DEBUG_WINDOW), NULL, DlgProc);
        ShowWindow(m_hDlg, SW_SHOW);

        HWND tab = DebugHandles::GetHandle(IDC_Hierarchy);
        TCITEMA tItem;
        tItem.mask = TCIF_TEXT;
        tItem.pszText = const_cast<char*>("World");
        TabCtrl_InsertItem(tab, 0, &tItem);

        tItem.pszText = const_cast<char*>("Screen");
        TabCtrl_InsertItem(tab, 1, &tItem);

        m_hFont = CreateFont(12, 0, 0, 0, 0, 0, 0, 0,
            ANSI_CHARSET,
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_DONTCARE,
            "MS Shell Dlg");
    }

    if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
        return E_FAIL;

    ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));
    m_d3dpp.Windowed = TRUE;
    m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    m_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    m_d3dpp.EnableAutoDepthStencil = TRUE;
    m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    //m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
        D3DCREATE_HARDWARE_VERTEXPROCESSING,
        &m_d3dpp, &m_pd3dDevice)))
    {
        if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
            D3DCREATE_SOFTWARE_VERTEXPROCESSING,
            &m_d3dpp, &m_pd3dDevice)))
        {
            return E_FAIL;
        }
    }

    ShowWindow(m_hWnd, SW_SHOWDEFAULT);
    UpdateWindow(m_hWnd);

    m_pd3dDevice->GetMaterial(&m_DefaultMaterial);
    m_pd3dDevice->GetTexture(0, &m_DefaultTexture);

    m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
    m_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
    m_pd3dDevice->SetRenderState(D3DRS_COLORVERTEX, TRUE);
    m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

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