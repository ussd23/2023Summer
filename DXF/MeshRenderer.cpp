#include "ComponentHeader.h"

MeshRenderer::MeshRenderer(const string& p_ModelName)
{
    m_ModelName = p_ModelName;
}

void MeshRenderer::Start()
{
    m_Transform = GetComponentFromObject(gameObject, Transform);

    m_MeshInfo = MeshManager::GetInstance()->GetMesh(m_ModelName);
}

void MeshRenderer::PreRender()
{
    if (m_Transform == nullptr) return;
    if (m_MeshInfo == nullptr) return;

    Vector3 pos = m_Transform->GetWorldPosition();
    Vector3 scale = m_Transform->GetWorldScale();

    float maxscale = max(scale.x, max(scale.y, scale.z));

    Vector3 sub = pos - Camera::main->m_Transform->GetWorldPosition();
    m_Distance = D3DXVec3LengthSq(&sub) - m_MeshInfo->farthestDistance * maxscale;

    if (g_Frustum->isIn(pos, m_MeshInfo->farthestDistance * maxscale))
    {
        g_TransformRenderList.push_back(this);
    }
}

void MeshRenderer::Render()
{
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

    for (DWORD i = 0; i < m_MeshInfo->dwNumMaterials; i++)
    {
        g_pd3dDevice->SetMaterial(&m_MeshInfo->pMeshMaterials[i]);
        g_pd3dDevice->SetTexture(0, m_MeshInfo->pMeshTextures[i]);
        // g_pd3dDevice->SetVertexShader()

        if (m_MeshInfo->pMesh == NULL) return;
        m_MeshInfo->pMesh->DrawSubset(i);
    }
}