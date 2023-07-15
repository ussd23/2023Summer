//-----------------------------------------------------------------------------
// File: VerticeRenderer
//
// Desc: 버텍스 렌더를 위한 컴포넌트
//
//		[Variables]
//		- transform: 오브젝트의 Transform 컴포넌트
//		- texturename: 텍스쳐의 파일명
//		- pTexture: 텍스쳐 인터페이스
//		- vertices: 버텍스 정보
//		- farthestDistance: 가장 먼 정점의 거리 (Frustum Culling에 사용)
//		- type: 기본 도형(primitive) 유형을 지정하는 enum
//		- startvertex: 출력을 시작할 버텍스의 인덱스
//		- count: 출력할 버텍스 단위의 수
//		- rectsize: 텍스쳐 파일의 분할 개수
//		- rectindex: 렌더링할 텍스쳐 파일의 인덱스
//
//		[Functions]
//		- Render: 렌더 실행
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
	float					farthestDistance;
	D3DPRIMITIVETYPE		type;
	UINT					startvertex;
	UINT					count;

public:
	Vector2					rectsize;
	Vector2					rectindex;

public:
	VerticeRenderer(vector<Vertex>, D3DPRIMITIVETYPE, UINT, UINT);
	VerticeRenderer(string, vector<Vertex>, D3DPRIMITIVETYPE, UINT, UINT);
	VerticeRenderer(string, Vector2, Vector2, vector<Vertex>, D3DPRIMITIVETYPE, UINT, UINT);
	void Render();

	void Start() override;
};

