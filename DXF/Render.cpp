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
    if (m_pd3dDevice->TestCooperativeLevel() != D3D_OK) return E_FAIL;

    m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER /*| D3DCLEAR_STENCIL*/,
        D3DCOLOR_ARGB(255, 0, 0, 0), 1.0f, 0);

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

        //// Turn on the zbuffer
        //m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, true);
        //// Turn on ambient lighting 
        //m_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);

        //// 초기화
        //m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
        //m_pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, false);
        //m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

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

        //if ( DebugModeCls::ISStencil )
        //{
        //    m_pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, true);
        //    m_pd3dDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
        //    m_pd3dDevice->SetRenderState(D3DRS_STENCILREF, 0x1);
        //    m_pd3dDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
        //    m_pd3dDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
        //    m_pd3dDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
        //    m_pd3dDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
        //    m_pd3dDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);

        //    // disable writes to the depth and back buffers
        //    m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, false);
        //    m_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
        //    m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
        //    m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
        //    m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
        //}


        // 스텐실 마스크 영역을 정의하는 오브젝트 렌더링(뷰박스)
        for (int i = 0; i < Var::StencilMaskRenderList.size(); ++i)
        {
            Var::StencilMaskRenderList[i]->Render();
        }


        //if ( DebugModeCls::ISStencil2 )
        //{
        //    m_pd3dDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
        //    m_pd3dDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

        //    //m_pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, true);
        //    m_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

        //    m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
        //    m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
        //    m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        //    m_pd3dDevice->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
        //}

        // Render objects that should only appear inside the masked area
        for (int i = 0; i < Var::StenciledObjectRenderList.size(); ++i)
        {
            Var::StenciledObjectRenderList[i]->Render();
        }

        m_pd3dDevice->EndScene();
    }

    m_pd3dDevice->Present(NULL, NULL, NULL, NULL);

    return S_OK;
}