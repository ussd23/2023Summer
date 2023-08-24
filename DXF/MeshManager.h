//-----------------------------------------------------------------------------
// File: MeshManager
//
// Desc: �޽� ������ ���� �� ��ȯ�ϴ� Ŭ����
//
//		[Class]
//		- MeshInfo: �޽� ������ �����ϴ� Ŭ����
//			- pMesh: �޽� �������̽�
//			- pMeshMaterials: ���Ǵ� ��Ƽ���� �迭
//			- pMeshTextures: ���Ǵ� �ؽ��� �迭
//			- dwNumMaterials: ��Ƽ������ ����
//			- farthestDistance: ���� �� ������ �Ÿ� (Frustum Culling�� ���)
//
//		[Variables]
//		- m_MeshInfos: �޽� ���� ���
//		- m_MeshInfosMap: string ����� �޽� ���� ���
//
//		[Functions]
//		- GetMesh: 3d ������ ������� �޽� ������ �˻��Ͽ� ��ȯ
//		- Cleanup: �޽� ���� ����
//-----------------------------------------------------------------------------

#pragma once
#include "StandardLibrary.h"
#include "GetI.h"
#include "DXHeader.h"

class MeshInfo
{
public:
	LPD3DXMESH          pMesh = NULL;
	D3DMATERIAL9*		pMeshMaterials = NULL;
	LPDIRECT3DTEXTURE9* pMeshTextures = NULL;
	DWORD               dwNumMaterials = 0L;
	float				farthestDistance = 0.f;
};

class MeshManager : public GetI<MeshManager>
{
protected:
	vector<MeshInfo*>		m_MeshInfos;
	map<string, MeshInfo*>	m_MeshInfosMap;

public:
	MeshInfo* GetMesh(const string& p_Path);
	void Cleanup();
};

