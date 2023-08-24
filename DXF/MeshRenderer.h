//-----------------------------------------------------------------------------
// File: MeshRenderer
//
// Desc: �޽� ������ ���� ������Ʈ
//
//		[Variables]
//		- m_Transform: ������Ʈ�� Transform ������Ʈ
//		- m_Meshinfo: �޽� ����
//		- m_ModelName: �޽��� ���ϸ�
//
//		[Functions]
//		- Render: ���� ����
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