#include "DXHeader.h"
#include "Global.h"
#include "Functions.h"
#include "Time.h"
#include "Frustum.h"
#include "GameObject.h"
#include "Transform.h"
#include "RectTransform.h"
#include "Camera.h"
#include "Renderer.h"

Matrix16 DXFGame::viewMatrix;
Matrix16 DXFGame::projMatrix;

HRESULT DXFGame::SetupCamera()
{
    Camera* camera = Camera::main;
    if (camera == nullptr)
    {
        MessageBox(NULL, "Could not find Main camera", "No Camera", MB_OK);
        return E_FAIL;
    }

    D3DXMatrixLookAtLH(&viewMatrix, &camera->vEyePt, &camera->vLookatPt, &camera->vUpVec);
    g_pd3dDevice->SetTransform(D3DTS_VIEW, &viewMatrix);

    D3DXMatrixPerspectiveFovLH(&projMatrix, D3DX_PI / 4 - (camera->fovRate / (D3DX_PI * 5)), SCREENSIZEX / (float)SCREENSIZEY, 1.0f, 100.0f);
    g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &projMatrix);

    return S_OK;
}

HRESULT DXFGame::Render()
{
    g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
        D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    SetRect(&g_ScreenRect, 0, 0, SCREENSIZEX, SCREENSIZEY);

    g_CullingObjects = 0;

    if (SUCCEEDED(g_pd3dDevice->BeginScene()))
    {
        if (FAILED(SetupCamera())) return E_FAIL;

        // Frustum 생성
        Matrix16 matViewProj = viewMatrix * projMatrix;
        if (g_Frustum != nullptr) g_Frustum->MakeFrustum(&matViewProj);

        g_TransformRenderList.clear();
        g_RectTransformRenderList.clear();

        // Frustum Culling 적용
        if (g_RootObject != nullptr) g_RootObject->PreRender();
        if (g_RootRectObject != nullptr) g_RootRectObject->PreRender();

        // Transform을 사용하는 오브젝트 정렬 및 렌더링 (카메라와 가까운 순)
        sort(g_TransformRenderList.begin(), g_TransformRenderList.end(), Renderer::Compare);
        for (int i = 0; i < g_TransformRenderList.size(); ++i)
        {
            g_TransformRenderList[i]->Render();
        }

        // RectTransform을 사용하는 오브젝트 렌더링 (Parent/Child 순)
        for (int i = 0; i < g_RectTransformRenderList.size(); ++i)
        {
            g_RectTransformRenderList[i]->Render();
        }

        g_pd3dDevice->EndScene();
    }

    g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

    return S_OK;
}