//-----------------------------------------------------------------------------
// File: MeshRenderer
//
// Desc: 메쉬 렌더를 위한 컴포넌트
//
//		[Variables]
//		- m_Transform: 오브젝트의 Transform 컴포넌트
//		- m_Meshinfo: 메쉬 정보
//		- m_ModelName: 메쉬의 파일명
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
	Transform*			m_Transform;
	MeshInfo*			m_MeshInfo;
	string				m_ModelName;

public:
	MeshRenderer(const string& p_ModelName);

	void Start() override;
	void PreRender() override;
	void Render() override;

	SerializeFunction(MeshRenderer)
	{
		Serialize(m_ModelName);
	}
	DeserializeFunction()
	{
		Deserialize(m_ModelName);
	}
};