//-----------------------------------------------------------------------------
// File: Frustum
//
// Desc: 절두체 컬링에 사용되는 기능
//
//		[Variables]
//		- m_Vertex: 절두체를 구성하는 8개의 정점
//		- m_Plane: 절두체를 구성하는 6개의 평면
//
//		[Functions]
//      - MakeFrustum: 절두체 평면을 생성
//      - isIn: 해당 오브젝트가 절두체 안에 있는 지 여부 반환
//-----------------------------------------------------------------------------

#pragma once
#include "DXHeader.h"

class Frustum
{
protected:
	Vector3		m_Vertex[8];
	Plane		m_Plane[6];

public:
	void MakeFrustum(Matrix16* p_MatViewProj);
	bool isIn(Vector3 p_Position);
	bool isIn(Vector3 p_Position, float p_Radius);
};

