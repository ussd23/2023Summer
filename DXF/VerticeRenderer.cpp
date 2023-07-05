#include "ComponentHeader.h"

VerticeRenderer::VerticeRenderer(GameObject* _gameObject, vector<CUSTOMVERTEX> _vertices, D3DPRIMITIVETYPE _type, UINT _startvertex, UINT _count)
    : VerticeRenderer(_gameObject, "", _vertices, _type, _startvertex, _count) {}

VerticeRenderer::VerticeRenderer(GameObject* _gameObject, string _texturename, vector<CUSTOMVERTEX> _vertices, D3DPRIMITIVETYPE _type, UINT _startvertex, UINT _count)
    : VerticeRenderer(_gameObject, _texturename, D3DXVECTOR2(1, 1), D3DXVECTOR2(0, 0), _vertices, _type, _startvertex, _count) {}

VerticeRenderer::VerticeRenderer(GameObject* _gameObject, string _texturename, D3DXVECTOR2 _rectsize, D3DXVECTOR2 _rectindex, vector<CUSTOMVERTEX> _vertices, D3DPRIMITIVETYPE _type, UINT _startvertex, UINT _count)
{
    texturename = _texturename;
    gameObject = _gameObject;
    vertices = _vertices;
    rectsize = _rectsize;
    rectindex = _rectindex;
    type = _type;
    startvertex = _startvertex;
    count = _count;
}

void VerticeRenderer::Start()
{
    transform = GetComponentFromObject(gameObject, Transform);

    if (texturename.size() <= 0) return;
    
    pTexture = TextureManager::GetInstance()->GetTexture(texturename);
}

void VerticeRenderer::Render()
{
    if (transform == nullptr) return;

    if (FAILED(g_pd3dDevice->CreateVertexBuffer(vertices.size() * sizeof(CUSTOMVERTEX),
        0, D3DFVF_CUSTOMVERTEX,
        D3DPOOL_DEFAULT, &g_pVB, NULL)))
    {
        return;
    }

    D3DXVECTOR2 temp = D3DXVECTOR2(1 / rectsize.x, 1 / rectsize.y);

    CUSTOMVERTEX* pVertices;
    if (FAILED(g_pVB->Lock(0, 0, (void**)&pVertices, 0)))
        return;
    for (DWORD i = 0; i < vertices.size(); ++i)
    {
        CUSTOMVERTEX vertex = vertices[i];
        vertex.tu = rectindex.x * temp.x + (vertex.tu * temp.x);
        vertex.tv = rectindex.y * temp.y + (vertex.tv * temp.y);
        pVertices[i] = vertex;
    }
    g_pVB->Unlock();

    g_pd3dDevice->SetMaterial(&g_defaultMaterial);
    if (pTexture != NULL) g_pd3dDevice->SetTexture(0, pTexture);
    else
    {
        g_pd3dDevice->SetTexture(0, g_defaultTexture);
        g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
        g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
    }

    D3DXVECTOR3 pos = transform->GetWorldPosition();
    D3DXVECTOR3 rot = transform->GetWorldRotation();
    D3DXVECTOR3 scale = transform->GetWorldScale();

    D3DXMATRIXA16 matWorldPosition;
    D3DXMatrixTranslation(&matWorldPosition, pos.x, pos.y, pos.z);

    D3DXMATRIXA16 matWorldRotationX;
    D3DXMatrixRotationX(&matWorldRotationX, D3DXToRadian(rot.x));

    D3DXMATRIXA16 matWorldRotationY;
    D3DXMatrixRotationY(&matWorldRotationY, D3DXToRadian(rot.y));

    D3DXMATRIXA16 matWorldRotationZ;
    D3DXMatrixRotationZ(&matWorldRotationZ, D3DXToRadian(rot.z));

    D3DXMATRIXA16 matWorldScale;
    D3DXMatrixScaling(&matWorldScale, scale.x, scale.y, scale.z);

    D3DXMATRIXA16 matWorldSet;
    D3DXMatrixIdentity(&matWorldSet);
    matWorldSet = matWorldScale * matWorldRotationX * matWorldRotationY * matWorldRotationZ * matWorldPosition;
    g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorldSet);
    g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
    g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
    g_pd3dDevice->DrawPrimitive(type, startvertex, count);
}
