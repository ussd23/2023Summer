//-----------------------------------------------------------------------------
// File: MeshRenderer
//
// Desc: 메쉬 렌더를 위한 컴포넌트
//
//		[Variables]
//		- transform: 오브젝트의 Transform 컴포넌트
//		- meshinfo: 메쉬 정보
//		- modelname: 메쉬의 파일명
//
//		[Functions]
//		- Render: 렌더 실행
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"
#include "Renderer.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class Transform;
class MeshInfo;

class MeshRenderer : public Renderer
{
protected:
	Transform*			transform;
	MeshInfo*			meshinfo;
	string				modelname;

public:
	MeshRenderer(string);

	void Start() override;
	void PreRender() override;
	void Render() override;
};

