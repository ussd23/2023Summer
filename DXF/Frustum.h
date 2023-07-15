//-----------------------------------------------------------------------------
// File: Frustum
//
// Desc: ����ü �ø��� ���Ǵ� ���
//
//		[Variables]
//		- vertex: ����ü�� �����ϴ� 8���� ����
//		- plane: ����ü�� �����ϴ� 6���� ���
//
//		[Functions]
//      - MakeFrustum: ����ü ����� ����
//      - isIn: �ش� ������Ʈ�� ����ü �ȿ� �ִ� �� ���� ��ȯ
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

