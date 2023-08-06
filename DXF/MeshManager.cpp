#include "MeshManager.h"
#include "TextureManager.h"

MeshInfo* MeshManager::GetMesh(const string& p_Path)
{
    map<string, MeshInfo*>::iterator iter = m_MeshInfosMap.find(p_Path);
    if (iter != m_MeshInfosMap.end())
    {
        return iter->second;
    }

    MeshInfo* meshinfo = new MeshInfo();

    LPD3DXBUFFER pD3DXMtrlBuffer;

    string path = "resources\\" + p_Path;
    if (FAILED(D3DXLoadMeshFromX(path.c_str(), D3DXMESH_SYSTEMMEM, DXFGame::m_pd3dDevice, NULL, &pD3DXMtrlBuffer, NULL, &meshinfo->dwNumMaterials, &meshinfo->pMesh)))
    {
        path = "..\\resources\\" + p_Path;
        if (FAILED(D3DXLoadMeshFromX(path.c_str(), D3DXMESH_SYSTEMMEM, DXFGame::m_pd3dDevice, NULL, &pD3DXMtrlBuffer, NULL, &meshinfo->dwNumMaterials, &meshinfo->pMesh)))
        {
            path = "..\\..\\resources\\", p_Path;
            if (FAILED(D3DXLoadMeshFromX(path.c_str(), D3DXMESH_SYSTEMMEM, DXFGame::m_pd3dDevice, NULL, &pD3DXMtrlBuffer, NULL, &meshinfo->dwNumMaterials, &meshinfo->pMesh)))
            {
                string text = "Could not find mesh file: " + p_Path;
                MessageBox(NULL, text.c_str(), "Mesh Load Failed", MB_OK);
                return nullptr;
            }
        }
    }

    D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
    meshinfo->pMeshMaterials = new D3DMATERIAL9[meshinfo->dwNumMaterials];
    if (meshinfo->pMeshMaterials == NULL) return nullptr;
    meshinfo->pMeshTextures = new LPDIRECT3DTEXTURE9[meshinfo->dwNumMaterials];
    if (meshinfo->pMeshTextures == NULL) return nullptr;

    for (DWORD i = 0; i < meshinfo->dwNumMaterials; i++)
    {
        meshinfo->pMeshMaterials[i] = d3dxMaterials[i].MatD3D;

        meshinfo->pMeshMaterials[i].Ambient = meshinfo->pMeshMaterials[i].Diffuse;

        meshinfo->pMeshTextures[i] = NULL;
        if (d3dxMaterials[i].pTextureFilename != NULL &&
            lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
        {
            meshinfo->pMeshTextures[i] = TextureManager::GetInstance()->GetTexture(d3dxMaterials[i].pTextureFilename);
        }
    }

    pD3DXMtrlBuffer->Release();

    D3DXVECTOR3* pVertices;
    float farthest = 0.f;

    meshinfo->pMesh->GetVertexBuffer(&DXFGame::m_pVB);
    DXFGame::m_pVB->Lock(0, 0, (void**)&pVertices, 0);

    for (DWORD i = 0; i < meshinfo->pMesh->GetNumVertices(); ++i)
    {
        D3DXVECTOR3 vertex = pVertices[i];
        float distance = D3DXVec3Length(&vertex);

        if (distance > farthest)
        {
            farthest = distance;
        }
    }
    DXFGame::m_pVB->Unlock();

    meshinfo->farthestDistance = farthest;

    m_MeshInfos.push_back(meshinfo);
    m_MeshInfosMap.insert(make_pair(p_Path, meshinfo));

    return meshinfo;
}

void MeshManager::Cleanup()
{
    for (int i = 0; i < m_MeshInfos.size(); ++i)
    {
        if (m_MeshInfos[i]->pMeshMaterials != NULL)
            delete[] m_MeshInfos[i]->pMeshMaterials;

        if (m_MeshInfos[i]->pMeshTextures)
        {
            for (DWORD j = 0; j < m_MeshInfos[i]->dwNumMaterials; j++)
            {
                if (m_MeshInfos[i]->pMeshTextures[j])
                    m_MeshInfos[i]->pMeshTextures[j]->Release();
            }
            delete[] m_MeshInfos[i]->pMeshTextures;
        }
        if (m_MeshInfos[i]->pMesh != NULL)
            m_MeshInfos[i]->pMesh->Release();

        delete m_MeshInfos[i];
    }
}