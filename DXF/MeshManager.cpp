#include "MeshManager.h"
#include "TextureManager.h"

MeshInfo* MeshManager::GetMesh(const string& _filepath)
{
    map<string, MeshInfo*>::iterator iter = meshinfosmap.find(_filepath);
    if (iter != meshinfosmap.end())
    {
        return iter->second;
    }

    MeshInfo* meshinfo = new MeshInfo();

    LPD3DXBUFFER pD3DXMtrlBuffer;

    string path = "resources\\" + _filepath;
    if (FAILED(D3DXLoadMeshFromX(path.c_str(), D3DXMESH_SYSTEMMEM, g_pd3dDevice, NULL, &pD3DXMtrlBuffer, NULL, &meshinfo->dwNumMaterials, &meshinfo->pMesh)))
    {
        path = "..\\resources\\" + _filepath;
        if (FAILED(D3DXLoadMeshFromX(path.c_str(), D3DXMESH_SYSTEMMEM, g_pd3dDevice, NULL, &pD3DXMtrlBuffer, NULL, &meshinfo->dwNumMaterials, &meshinfo->pMesh)))
        {
            path = "..\\..\\resources\\", _filepath;
            if (FAILED(D3DXLoadMeshFromX(path.c_str(), D3DXMESH_SYSTEMMEM, g_pd3dDevice, NULL, &pD3DXMtrlBuffer, NULL, &meshinfo->dwNumMaterials, &meshinfo->pMesh)))
            {
                MessageBox(NULL, "Could not find mesh file", "Mesh Load Failed", MB_OK);
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

    meshinfos.push_back(meshinfo);
    meshinfosmap.insert(make_pair(_filepath, meshinfo));

    return meshinfo;
}

void MeshManager::Cleanup()
{
    for (int i = 0; i < meshinfos.size(); ++i)
    {
        if (meshinfos[i]->pMeshMaterials != NULL)
            delete[] meshinfos[i]->pMeshMaterials;

        if (meshinfos[i]->pMeshTextures)
        {
            for (DWORD j = 0; j < meshinfos[i]->dwNumMaterials; j++)
            {
                if (meshinfos[i]->pMeshTextures[j])
                    meshinfos[i]->pMeshTextures[j]->Release();
            }
            delete[] meshinfos[i]->pMeshTextures;
        }
        if (meshinfos[i]->pMesh != NULL)
            meshinfos[i]->pMesh->Release();

        delete meshinfos[i];
    }
}