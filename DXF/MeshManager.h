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
//		- meshinfos: �޽� ���� ���
//		- meshinfosmap: string ����� �޽� ���� ���
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
	vector<MeshInfo*>		meshinfos;
	map<string, MeshInfo*>	meshinfosmap;

public:
	MeshInfo* GetMesh(const string&);
	void Cleanup();
};

