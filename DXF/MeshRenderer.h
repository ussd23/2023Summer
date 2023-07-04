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
#include "DXHeader.h"
#include "StandardLibrary.h"

class Transform;
class MeshInfo;

class MeshRenderer : public Component
{
protected:
	Transform*			transform;
	MeshInfo*			meshinfo;
	string				modelname;

public:
	MeshRenderer(GameObject*, string);
	void Render();

	void Start() override;
};

