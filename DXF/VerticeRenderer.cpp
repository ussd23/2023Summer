#include "ComponentHeader.h"

VerticeRenderer::VerticeRenderer(vector<Vertex> p_Vertices, D3DPRIMITIVETYPE p_Type, UINT p_StartVertex, UINT p_Count)
    : VerticeRenderer("", p_Vertices, p_Type, p_StartVertex, p_Count) {}

VerticeRenderer::VerticeRenderer(string p_TextureName, vector<Vertex> p_Vertices, D3DPRIMITIVETYPE p_Type, UINT p_StartVertex, UINT p_Count)
    : VerticeRenderer(p_TextureName, Vector2(1, 1), Vector2(0, 0), p_Vertices, p_Type, p_StartVertex, p_Count) {}

VerticeRenderer::VerticeRenderer(string p_TextureName, Vector2 p_RectSize, Vector2 p_RectIndex, vector<Vertex> p_Vertices, D3DPRIMITIVETYPE p_Type, UINT p_StartVertex, UINT p_Count)
{
    m_TextureName = p_TextureName;
    m_Vertices = p_Vertices;
    m_RectSize = p_RectSize;
    m_RectIndex = p_RectIndex;
    m_Type = p_Type;
    m_StartVertex = p_StartVertex;
    m_Count = p_Count;
}

void VerticeRenderer::Start()
{
    m_Transform = GetComponentFromObject(gameObject, Transform);

    if (m_TextureName.size() <= 0) return;
    
    m_Texture = TextureManager::GetInstance()->GetTexture(m_TextureName);

    float farthest = 0.f;

    for (DWORD i = 0; i < m_Vertices.size(); ++i)
    {
        Vector3 vertex = Vector3(m_Vertices[i].x, m_Vertices[i].y, m_Vertices[i].z);
        float distance = D3DXVec3LengthSq(&vertex);

        if (distance > farthest)
        {
            farthest = distance;
        }
    }

    m_FarthestDistance = sqrt(farthest);
}

void VerticeRenderer::PreRender()
{
    if (m_Transform == nullptr) return;

    Vector3 pos = m_Transform->GetWorldPosition();
    Vector3 scale = m_Transform->GetWorldScale();

    float maxscale = max(scale.x, max(scale.y, scale.z));

    Vector3 sub = pos - Camera::main->m_Transform->GetWorldPosition();
    m_Distance = D3DXVec3Length(&sub) - m_FarthestDistance * maxscale;

    if (g_Frustum->isIn(pos, m_FarthestDistance * maxscale))
    {
        g_TransformRenderList.push_back(this);
    }
}

void VerticeRenderer::Render()
{
    if (FAILED(g_pd3dDevice->CreateVertexBuffer(m_Vertices.size() * sizeof(Vertex),
        0, D3DFVF_CUSTOMVERTEX,
        D3DPOOL_DEFAULT, &g_pVB, NULL)))
    {
        return;
    }

    Vector2 temp = Vector2(1 / m_RectSize.x, 1 / m_RectSize.y);

    Vertex* pVertices;
    if (FAILED(g_pVB->Lock(0, 0, (void**)&pVertices, 0)))
        return;
    for (DWORD i = 0; i < m_Vertices.size(); ++i)
    {
        Vertex vertex = m_Vertices[i];
        vertex.tu = m_RectIndex.x * temp.x + (vertex.tu * temp.x);
        vertex.tv = m_RectIndex.y * temp.y + (vertex.tv * temp.y);
        pVertices[i] = vertex;
    }
    g_pVB->Unlock();

    g_pd3dDevice->SetMaterial(&g_defaultMaterial);
    if (m_Texture != NULL) g_pd3dDevice->SetTexture(0, m_Texture);
    else
    {
        g_pd3dDevice->SetTexture(0, g_defaultTexture);
        g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
        g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
    }

    Vector3 pos = m_Transform->GetWorldPosition();
    Vector3 rot = m_Transform->GetWorldRotation();
    Vector3 scale = m_Transform->GetWorldScale();

    Matrix16 matWorldPosition;
    D3DXMatrixTranslation(&matWorldPosition, pos.x, pos.y, pos.z);

    Matrix16 matWorldRotationX;
    D3DXMatrixRotationX(&matWorldRotationX, D3DXToRadian(rot.x));

    Matrix16 matWorldRotationY;
    D3DXMatrixRotationY(&matWorldRotationY, D3DXToRadian(rot.y));

    Matrix16 matWorldRotationZ;
    D3DXMatrixRotationZ(&matWorldRotationZ, D3DXToRadian(rot.z));

    Matrix16 matWorldScale;
    D3DXMatrixScaling(&matWorldScale, scale.x, scale.y, scale.z);

    Matrix16 matWorldSet;
    D3DXMatrixIdentity(&matWorldSet);
    matWorldSet = matWorldScale * matWorldRotationX * matWorldRotationY * matWorldRotationZ * matWorldPosition;
    g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorldSet);
    g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(Vertex));
    g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
    g_pd3dDevice->DrawPrimitive(m_Type, m_StartVertex, m_Count);
}
