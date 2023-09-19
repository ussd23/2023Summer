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
    m_pd3dDevice->SetTransform(D3DTS_VIEW, &m_ViewMatrix);

    D3DXMatrixPerspectiveFovLH(&m_ProjMatrix, D3DX_PI * 0.25f - (camera->m_FovRate / (D3DX_PI * 5)), m_Resolution.x / m_Resolution.y, 1.0f, m_RenderDistance);
    m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

    return S_OK;
}

HRESULT DXFGame::Render()
{
    m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
        D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    SetRect(&Var::ScreenRect, 0, 0, m_Resolution.x, m_Resolution.y);

    Var::CullingObjects = 0;

    if (SUCCEEDED(m_pd3dDevice->BeginScene()))
    {
        if (FAILED(SetupCamera())) return E_FAIL;

        // Frustum 생성
        Matrix16 matViewProj = m_ViewMatrix * m_ProjMatrix;
        if (Var::Frustum != nullptr) Var::Frustum->MakeFrustum(&matViewProj);

        Var::TransformRenderList.clear();
        Var::RectTransformRenderList.clear();
        Var::StencilMaskRenderList.clear();
        Var::StenciledObjectRenderList.clear();

        // Frustum Culling 적용
        if (Var::RootObject != nullptr) Var::RootObject->PreRender();
        if (Var::RootRectObject != nullptr) Var::RootRectObject->PreRender();

        m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        m_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
        m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

        // 1. stencil setting 
        m_pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
        m_pd3dDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
        m_pd3dDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
        m_pd3dDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
        m_pd3dDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
        m_pd3dDevice->SetRenderState(D3DRS_STENCILREF, 0x1);
        m_pd3dDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);

        // 스텐실 마스크 영역을 정의하는 오브젝트 렌더링(뷰박스)
        for (int i = 0; i < Var::StencilMaskRenderList.size(); ++i)
        {
            Var::StencilMaskRenderList[i]->Render();
        }

        m_pd3dDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
        m_pd3dDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);
        m_pd3dDevice->SetRenderState(D3DRS_STENCILREF, 0x1);
        m_pd3dDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);

        m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
        m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

        // Render objects that should only appear inside the masked area
        for (int i = 0; i < Var::StenciledObjectRenderList.size(); ++i)
        {
            Var::StenciledObjectRenderList[i]->Render();
        }

        // Reset stencil states
        m_pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
        m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);         // End the scene

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


        m_pd3dDevice->EndScene();
    }

    m_pd3dDevice->Present(NULL, NULL, NULL, NULL);

    return S_OK;
}