#include "ComponentHeader.h"

MeshRenderer::MeshRenderer(const string& p_ModelName)
    : m_ModelName(p_ModelName) {}

void MeshRenderer::Start()
{
    m_Transform = GetComponentFromObject(gameObject, Transform);

    m_MeshInfo = MeshManager::GetInstance()->GetMesh(m_ModelName);
}

void MeshRenderer::PreRender()
{
    if (m_Transform == nullptr) return;
    if (m_MeshInfo == nullptr) return;
    if (m_MeshInfo->pMesh == NULL) return;

    Vector3 pos = m_Transform->GetWorldPosition();
    Vector3 scale = m_Transform->GetWorldScale();

    float maxscale = max(scale.x, max(scale.y, scale.z));

    Vector3 sub = pos - Camera::main->m_Transform->GetWorldPosition();
    m_Distance = D3DXVec3LengthSq(&sub) - m_MeshInfo->farthestDistance * maxscale;

    if (Var::Frustum->isIn(pos, m_MeshInfo->farthestDistance * maxscale))
    {
        Var::TransformRenderList.push_back(this);
    }
}

void MeshRenderer::Render()
{
    Vector3 pos = m_Transform->GetWorldPosition();
    Quaternion rot = m_Transform->GetWorldRotation();
    Vector3 scale = m_Transform->GetWorldScale();

    Matrix16 matWorldPosition;
    D3DXMatrixTranslation(&matWorldPosition, pos.x, pos.y, pos.z);

    Matrix16 matWorldRotation;
    D3DXMatrixRotationQuaternion(&matWorldRotation, &rot);

    Matrix16 matWorldScale;
    D3DXMatrixScaling(&matWorldScale, scale.x, scale.y, scale.z);

    Matrix16 matWorldSet;
    D3DXMatrixIdentity(&matWorldSet);
    matWorldSet = matWorldScale * matWorldRotation * matWorldPosition;
    DXFGame::m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorldSet);

    for (DWORD i = 0; i < m_MeshInfo->dwNumMaterials; i++)
    {
        DXFGame::m_pd3dDevice->SetMaterial(&m_MeshInfo->pMeshMaterials[i]);
        DXFGame::m_pd3dDevice->SetTexture(0, m_MeshInfo->pMeshTextures[i]);
        //DXFGame::m_pd3dDevice->SetVertexShader();

        m_MeshInfo->pMesh->DrawSubset(i);
    }
}