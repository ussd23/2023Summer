#include "DXHeader.h"
#include "Global.h"
#include "Functions.h"
#include "Time.h"
#include "GameObject.h"
#include "Transform.h"
#include "RectTransform.h"
#include "Camera.h"

HRESULT SetupCamera()
{
    Camera* camera = Camera::main;
    if (camera == nullptr)
    {
        MessageBox(NULL, "Could not find Main camera", "No Camera", MB_OK);
        return E_FAIL;
    }

    Matrix16 matView;
    D3DXMatrixLookAtLH(&matView, &camera->vEyePt, &camera->vLookatPt, &camera->vUpVec);
    g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

    Matrix16 matProj;
    D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4 - (camera->fovRate / (D3DX_PI * 5)), SCREENSIZEX / (float)SCREENSIZEY, 1.0f, 100.0f);
    g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);

    return S_OK;
}

HRESULT Render()
{
    g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
        D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    //* 카메라컬링
    //* 오브젝트 컬링
    //* 소팅

    if (SUCCEEDED(g_pd3dDevice->BeginScene()))
    {
        if (FAILED(SetupCamera())) return E_FAIL;

        if (g_RootObject != nullptr) g_RootObject->Render();
        if (g_RootRectObject != nullptr) g_RootRectObject->Render();

        g_pd3dDevice->EndScene();
    }

    g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

    return S_OK;
}