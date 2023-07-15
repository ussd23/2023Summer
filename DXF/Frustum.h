//-----------------------------------------------------------------------------
// File: Frustum
//
// Desc: 절두체 컬링에 사용되는 기능
//
//		[Variables]
//		- vertex: 절두체를 구성하는 8개의 정점
//		- plane: 절두체를 구성하는 6개의 평면
//
//		[Functions]
//      - MakeFrustum: 절두체 평면을 생성
//      - isIn: 해당 오브젝트가 절두체 안에 있는 지 여부 반환
//-----------------------------------------------------------------------------

#pragma once
#include "DXHeader.h"

#define PLANE_EPSILON   5.0f

class Frustum
{
private:
	Vector3		vertex[8];
	Plane		plane[6];

public:
	void MakeFrustum(Matrix16*);
	bool isIn(Vector3);
	bool isIn(Vector3, float);
};

