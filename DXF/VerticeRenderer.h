//-----------------------------------------------------------------------------
// File: VerticeRenderer
//
// Desc: ���ؽ� ������ ���� ������Ʈ
//
//		[Variables]
//		- m_Transform: ������Ʈ�� Transform ������Ʈ
//		- m_TextureName: �ؽ����� ���ϸ�
//		- m_Texture: �ؽ��� �������̽�
//		- m_Vertices: ���ؽ� ����
//		- m_FarthestDistance: ���� �� ������ �Ÿ� (Frustum Culling�� ���)
//		- m_Type: �⺻ ����(primitive) ������ �����ϴ� enum
//		- m_StartVertex: ����� ������ ���ؽ��� �ε���
//		- m_Count: ����� ���ؽ� ������ ��
//		- m_RectSize: �ؽ��� ������ ���� ����
//		- m_RectIndex: �������� �ؽ��� ������ �ε���
//
//		[Functions]
//		- Render: ���� ����
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"
#include "Renderer.h"
#include "DXHeader.h"
#include "CustomVertex.h"
#include "StandardLibrary.h"

class Transform;
class RectTransform;

class VerticeRenderer : public Renderer
{
protected:
	Transform*				m_Transform;
	string					m_TextureName;
	LPDIRECT3DTEXTURE9		m_Texture = NULL;
	float					m_FarthestDistance;
	D3DPRIMITIVETYPE		m_Type;
	UINT					m_StartVertex;
	UINT					m_Count;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	vector<Vertex>			m_Vertices;
	Vector2					m_PastRectSize;
	Vector2					m_PastRectIndex;
	float					m_VerticeChanged = false;

public:
	Vector2					m_RectSize;
	Vector2					m_RectIndex;

public:
	VerticeRenderer(vector<Vertex> p_Vertices, D3DPRIMITIVETYPE p_Type, UINT p_StartVertex, UINT p_Count);
	VerticeRenderer(string p_TextureName, vector<Vertex> p_Vertices, D3DPRIMITIVETYPE p_Type, UINT p_StartVertex, UINT p_Count);
	VerticeRenderer(string p_TextureName, Vector2 p_RectSize, Vector2 p_RectIndex, vector<Vertex> p_Vertices, D3DPRIMITIVETYPE p_Type, UINT p_StartVertex, UINT p_Count);

	void ChangeVertices(vector<Vertex> p_Vertices);
	vector<Vertex> GetVertices();

	void Start() override;
	void PreRender() override;
	void Render() override;
	void OnDestroy() override;

	SerializeFunction(VerticeRenderer)
	{
		Serialize(m_TextureName);
		VectorSerialize(m_Vertices);
		Serialize(m_Type);
		Serialize(m_StartVertex);
		Serialize(m_Count);
		Serialize(m_RectSize);
		Serialize(m_RectIndex);
	}
};

