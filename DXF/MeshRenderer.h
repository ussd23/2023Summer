//-----------------------------------------------------------------------------
// File: MeshRenderer
//
// Desc: �޽� ������ ���� ������Ʈ
//
//		[Variables]
//		- transform: ������Ʈ�� Transform ������Ʈ
//		- meshinfo: �޽� ����
//		- modelname: �޽��� ���ϸ�
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
	Transform*			transform;
	MeshInfo*			meshinfo;
	string				modelname;

public:
	MeshRenderer(string);

	void Start() override;
	void PreRender() override;
	void Render() override;
};

