#include "ComponentHeader.h"

SpriteRenderer::SpriteRenderer(string p_TextureName)
    : SpriteRenderer(p_TextureName, 0xffffffff, Vector2(1, 1), Vector2(0, 0), Vector2(0.5f, 0.5f)) {}

SpriteRenderer::SpriteRenderer(string p_TextureName, Vector2 p_RectSize, Vector2 p_RectIndex)
    : SpriteRenderer(p_TextureName, 0xffffffff, p_RectSize, p_RectIndex, Vector2(0.5f, 0.5f)) {}

SpriteRenderer::SpriteRenderer(string p_TextureName, DWORD p_Color, Vector2 p_RectSize, Vector2 p_RectIndex)
    : SpriteRenderer(p_TextureName, p_Color, p_RectSize, p_RectIndex, Vector2(0.5f, 0.5f)) {}

SpriteRenderer::SpriteRenderer(string p_TextureName, DWORD p_Color, Vector2 p_RectSize, Vector2 p_RectIndex, Vector2 p_RotatePivot)
{
    m_TextureName = p_TextureName;
    m_Color = p_Color;
    m_RectSize = p_RectSize;
    m_RectIndex = p_RectIndex;
    m_RotatePivot = p_RotatePivot;
}

void SpriteRenderer::Start()
{
    m_RectTransform = GetComponentFromObject(gameObject, RectTransform);

    if (m_TextureName.size() <= 0) return;

    m_Texture = TextureManager::GetInstance()->GetTexture(m_TextureName);

    if (m_Texture == NULL) return;

    D3DSURFACE_DESC desc;
    m_Texture->GetLevelDesc(0, &desc);
    SetRect(&m_TextureSize, 0, 0, desc.Width, desc.Height);
}

void SpriteRenderer::PreRender()
{
    if (m_RectTransform == nullptr) return;
    if (m_Texture == NULL) return;

    Vector2 pos = m_RectTransform->GetScreenPosition();
    Vector2 scale = m_RectTransform->GetScreenScale();
    Vector2 size = m_RectTransform->m_Size;

    RECT rect;
    SetRect(&rect, pos.x - size.x * scale.x, pos.y - size.y * scale.y, pos.x + size.x * scale.x, pos.y + size.y * scale.y);

    if (Functions::Inner(rect, Var::ScreenRect))
    {
        //if (m_RectTransform->gameObject->m_Name.compare("viewbox") == 0)    //뷰박스를 스텐실 마스크영역으로 지정
        //{
        //    Var::StencilMaskRenderList.push_back(this);
        //}
        //else if (m_RectTransform->GetParent()->gameObject->m_Name.compare("content Text") == 0)   //콘텐츠박스의 자식 오브젝트라면 스텐실이 적용되는 오브젝트로 지정
        //{
        //    Var::StenciledObjectRenderList.push_back(this);
        //}
        //else if (m_RectTransform->GetParent()->gameObject->m_Name.compare("content Sprite") == 0)   //콘텐츠박스의 자식 오브젝트라면 스텐실이 적용되는 오브젝트로 지정
        //{
        //    Var::StenciledObjectRenderList.push_back(this);
        //}
        //else if (m_RectTransform->GetParent()->gameObject->m_Name.compare("HorizontalScrollBar") == 0)   //콘텐츠박스의 자식 오브젝트라면 스텐실이 적용되는 오브젝트로 지정
        //{
        //    Var::StenciledObjectRenderList.push_back(this);
        //}
        //else
        //{
        //    Var::RectTransformRenderList.push_back(this);
        //}
        Var::RectTransformRenderList.push_back(this);
    }
}

void SpriteRenderer::Render()
{
    Vector2 temp(m_TextureSize.right / m_RectSize.x, m_TextureSize.bottom / m_RectSize.y);
    RECT rect;
    SetRect(&rect, m_RectIndex.x * temp.x, m_RectIndex.y * temp.y, (m_RectIndex.x + 1) * temp.x, (m_RectIndex.y + 1) * temp.y);
    
    Vector2 pos = m_RectTransform->GetScreenPosition();
    Vector3 rot = Functions::QuaternionToEuler(m_RectTransform->GetScreenRotation());
    Vector2 scale = m_RectTransform->GetScreenScale();
    Vector2 size = m_RectTransform->m_Size;

	Matrix matScreenPosition;
	D3DXMatrixTranslation(&matScreenPosition, pos.x - size.x * scale.x * 0.5f, pos.y - size.y * scale.y * 0.5f, 0);
    
    Vector2 pivot(size.x * scale.x * m_RotatePivot.x, size.y * scale.y * m_RotatePivot.y);
    Matrix matScreenRotation;
    D3DXMatrixTransformation2D(&matScreenRotation, NULL, 0, NULL, &pivot, D3DXToRadian(rot.z), NULL);

    Matrix matScreenScale;
    D3DXMatrixScaling(&matScreenScale, (size.x / temp.x) * scale.x, (size.y / temp.y) * scale.y, 0);

    Matrix16 matScreenSet;
    D3DXMatrixIdentity(&matScreenSet);
    matScreenSet = matScreenScale * matScreenRotation * matScreenPosition;
	DXFGame::m_pSprite->SetTransform(&matScreenSet);
    DXFGame::m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

    //if (m_RectTransform->gameObject->m_Name.compare("viewbox") == 0)
    //{
    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, true);
    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_STENCILREF, 0x1);
    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);

    //    // disable writes to the depth and back buffers
    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, false);
    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
    //}
    //else if (m_RectTransform->GetParent()->gameObject->m_Name.compare("contentbox") == 0)
    //{
    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    //    DXFGame::m_pd3dDevice->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
    //}
    //else if (m_RectTransform->gameObject->m_Name.compare("contentbox") == 0)
    //{
    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, true);
    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
    //    DXFGame::m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    //    DXFGame::m_pd3dDevice->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
    //}

    DXFGame::m_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
    DXFGame::m_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
    
    DXFGame::m_pSprite->Draw(m_Texture, &rect, NULL, NULL, m_Color);
    DXFGame::m_pSprite->End();
}

void SpriteRenderer::ChangeSprite(string p_TextureName)
{
    m_TextureName = p_TextureName;

    if (m_TextureName.size() <= 0) return;

    m_Texture = TextureManager::GetInstance()->GetTexture(m_TextureName);

    if (m_Texture == NULL) return;

    D3DSURFACE_DESC desc;
    m_Texture->GetLevelDesc(0, &desc);
    SetRect(&m_TextureSize, 0, 0, desc.Width, desc.Height);
}