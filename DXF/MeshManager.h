//-----------------------------------------------------------------------------
// File: MeshManager
//
// Desc: 메쉬 정보를 생성 및 반환하는 클래스
//
//		[Class]
//		- MeshInfo: 메쉬 정보를 저장하는 클래스
//			- pMesh: 메쉬 인터페이스
//			- pMeshMaterials: 사용되는 머티리얼 배열
//			- pMeshTextures: 사용되는 텍스쳐 배열
//			- dwNumMaterials: 머티리얼의 개수
//			- farthestDistance: 가장 먼 정점의 거리 (Frustum Culling에 사용)
//
//		[Variables]
//		- meshinfos: 메쉬 정보 목록
//		- meshinfosmap: string 기반의 메쉬 정보 목록
//
//		[Functions]
//		- GetMesh: 3d 파일을 기반으로 메쉬 정보를 검색하여 반환
//		- Cleanup: 메쉬 정보 삭제
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

