//-----------------------------------------------------------------------------
// File: VerticeRenderer
//
// Desc: ���ؽ� ������ ���� ������Ʈ
//
//		[Variables]
//		- transform: ������Ʈ�� Transform ������Ʈ
//		- texturename: �ؽ����� ���ϸ�
//		- pTexture: �ؽ��� �������̽�
//		- vertices: ���ؽ� ����
//		- type: �⺻ ����(primitive) ������ �����ϴ� enum
//		- startvertex: ����� ������ ���ؽ��� �ε���
//		- count: ����� ���ؽ� ������ ��
//		- rectsize: �ؽ��� ������ ���� ����
//		- rectindex: �������� �ؽ��� ������ �ε���
//
//		[Functions]
//		- Render: ���� ����
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "CustomVertex.h"
#include "StandardLibrary.h"

class Transform;
class RectTransform;

class VerticeRenderer : public Component
{
protected:
	Transform*				transform;
	string					texturename;
	LPDIRECT3DTEXTURE9		pTexture = NULL;
	vector<Vertex>			vertices;
	D3DPRIMITIVETYPE		type;
	UINT					startvertex;
	UINT					count;

public:
	Vector2					rectsize;
	Vector2					rectindex;

public:
	VerticeRenderer(GameObject*, vector<Vertex>, D3DPRIMITIVETYPE, UINT, UINT);
	VerticeRenderer(GameObject*, string, vector<Vertex>, D3DPRIMITIVETYPE, UINT, UINT);
	VerticeRenderer(GameObject*, string, Vector2, Vector2, vector<Vertex>, D3DPRIMITIVETYPE, UINT, UINT);
	void Render();

	void Start() override;
};

