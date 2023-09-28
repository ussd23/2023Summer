//-----------------------------------------------------------------------------
// File: VerticeRenderer
//
// Desc: 버텍스 렌더를 위한 컴포넌트
//
//		[Variables]
//		- m_Transform: 오브젝트의 Transform 컴포넌트
//		- m_TextureName: 텍스쳐의 파일명
//		- m_Texture: 텍스쳐 인터페이스
//		- m_Vertices: 버텍스 정보
//		- m_FarthestDistance: 가장 먼 정점의 거리 (Frustum Culling에 사용)
//		- m_Type: 기본 도형(primitive) 유형을 지정하는 enum
//		- m_StartVertex: 출력을 시작할 버텍스의 인덱스
//		- m_Count: 출력할 버텍스 단위의 수
//		- m_RectSize: 텍스쳐 파일의 분할 개수
//		- m_RectIndex: 렌더링할 텍스쳐 파일의 인덱스
//
//		[Functions]
//		- Render: 렌더 실행
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

