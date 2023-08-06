#include "DXHeader.h"
#include "Global.h"
#include "Transform.h"
#include "RectTransform.h"
#include "Frustum.h"

HRESULT DXFGame::InitD3D(HWND hWnd)
{
    if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
        return E_FAIL;

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    //d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
        D3DCREATE_HARDWARE_VERTEXPROCESSING,
        &d3dpp, &m_pd3dDevice)))
    {
        if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
            D3DCREATE_SOFTWARE_VERTEXPROCESSING,
            &d3dpp, &m_pd3dDevice)))
        {
            return E_FAIL;
        }
    }

    m_pd3dDevice->GetMaterial(&m_defaultMaterial);
    m_pd3dDevice->GetTexture(0, &m_defaultTexture);

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