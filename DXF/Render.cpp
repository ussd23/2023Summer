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

HRESULT DXFGame::SetupCamera()
{
    Camera* camera = Camera::main;
    if (camera == nullptr)
    {
        MessageBox(NULL, "Could not find Main camera", "No Camera", MB_OK);
        return E_FAIL;
    }

    Transform* transform = GetComponentFromObject(camera->gameObject, Transform);
    Vector3 eyePt = transform->GetWorldPosition();

    D3DXMatrixLookAtLH(&m_ViewMatrix, &eyePt, &camera->m_LookatPt, &camera->m_UpVec);
    DXFGame::m_pd3dDevice->SetTransform(D3DTS_VIEW, &m_ViewMatrix);

    D3DXMatrixPerspectiveFovLH(&m_ProjMatrix, D3DX_PI * 0.25f - (camera->m_FovRate / (D3DX_PI * 5)), SCREENSIZEX / (float)SCREENSIZEY, 1.0f, 300.0f);
    DXFGame::m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

    return S_OK;
}

HRESULT DXFGame::Render()
{
    DXFGame::m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
        D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    SetRect(&Var::ScreenRect, 0, 0, SCREENSIZEX, SCREENSIZEY);

    Var::CullingObjects = 0;

    if (SUCCEEDED(DXFGame::m_pd3dDevice->BeginScene()))
    {
        if (FAILED(SetupCamera())) return E_FAIL;

        // Frustum 생성
        Matrix16 matViewProj = m_ViewMatrix * m_ProjMatrix;
        if (Var::Frustum != nullptr) Var::Frustum->MakeFrustum(&matViewProj);

        Var::TransformRenderList.clear();
        Var::RectTransformRenderList.clear();

        // Frustum Culling 적용
        if (Var::RootObject != nullptr) Var::RootObject->PreRender();
        if (Var::RootRectObject != nullptr) Var::RootRectObject->PreRender();

        // Transform을 사용하는 오브젝트 정렬 및 렌더링 (카메라와 가까운 순)
        sort(Var::TransformRenderList.begin(), Var::TransformRenderList.end(), Renderer::Compare);
        for (int i = 0; i < Var::TransformRenderList.size(); ++i)
        {
            Var::TransformRenderList[i]->Render();
        }

        // RectTransform을 사용하는 오브젝트 렌더링 (Parent/Child 순)
        for (int i = 0; i < Var::RectTransformRenderList.size(); ++i)
        {
            Var::RectTransformRenderList[i]->Render();
        }

        DXFGame::m_pd3dDevice->EndScene();
    }

    DXFGame::m_pd3dDevice->Present(NULL, NULL, NULL, NULL);

    return S_OK;
}