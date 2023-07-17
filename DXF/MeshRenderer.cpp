#include "ComponentHeader.h"

MeshRenderer::MeshRenderer(string _modelname)
{
    modelname = _modelname;
}

void MeshRenderer::Start()
{
    transform = GetComponentFromObject(gameObject, Transform);

    meshinfo = MeshManager::GetInstance()->GetMesh(modelname);
}

void MeshRenderer::PreRender()
{
    if (transform == nullptr) return;
    if (meshinfo == nullptr) return;

    Vector3 pos = transform->GetWorldPosition();
    Vector3 rot = transform->GetWorldRotation();
    Vector3 scale = transform->GetWorldScale();

    float maxscale = max(scale.x, max(scale.y, scale.z));

    Vector3 sub = pos - Camera::main->transform->GetWorldPosition();
    distance = D3DXVec3Length(&sub) - meshinfo->farthestDistance * maxscale;

    if (g_Frustum->isIn(pos, meshinfo->farthestDistance * maxscale))
    {
        g_TransformRenderList.push_back(this);
    }
}

void MeshRenderer::Render()
{
    Vector3 pos = transform->GetWorldPosition();
    Vector3 rot = transform->GetWorldRotation();
    Vector3 scale = transform->GetWorldScale();

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

    for (DWORD i = 0; i < meshinfo->dwNumMaterials; i++)
    {
        g_pd3dDevice->SetMaterial(&meshinfo->pMeshMaterials[i]);
        g_pd3dDevice->SetTexture(0, meshinfo->pMeshTextures[i]);
        // g_pd3dDevice->SetVertexShader()

        if (meshinfo->pMesh == NULL) return;
        meshinfo->pMesh->DrawSubset(i);
    }
}