#include "DXHeader.h"
#include "Global.h"
#include "Transform.h"
#include "RectTransform.h"
#include "Frustum.h"

HRESULT DXFGame::InitD3D(HWND hWnd)
{
    if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
        return E_FAIL;

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp, &g_pd3dDevice)))
    {
        return E_FAIL;
    }

    g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
    g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
    g_pd3dDevice->SetRenderState(D3DRS_COLORVERTEX, TRUE);
    g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

    g_Frustum = new Frustum();

    D3DXCreateSprite(g_pd3dDevice, &g_pSprite);

    g_RootObject = new GameObject("RootObject");
    g_RootTransform = new Transform(Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 0.f), Vector3(1.f, 1.f, 1.f));
    AddComponentToObject(g_RootObject, g_RootTransform);

    g_RootRectObject = new GameObject("RootRectObject");
    g_RootRectTransform = new RectTransform(Vector2(0.f, 0.f), Vector3(0.f, 0.f, 0.f), Vector2(1.f, 1.f), Vector2(0.f, 0.f));
    AddComponentToObject(g_RootRectObject, g_RootRectTransform);

    g_Objects.push_back(g_RootObject);
    g_Objects.push_back(g_RootRectObject);

    return S_OK;
}