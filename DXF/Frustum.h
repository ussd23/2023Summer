//-----------------------------------------------------------------------------
// File: Frustum
//
// Desc: ����ü �ø��� ���Ǵ� ���
//
//		[Variables]
//		- m_Vertex: ����ü�� �����ϴ� 8���� ����
//		- m_Plane: ����ü�� �����ϴ� 6���� ���
//
//		[Functions]
//      - MakeFrustum: ����ü ����� ����
//      - isIn: �ش� ������Ʈ�� ����ü �ȿ� �ִ� �� ���� ��ȯ
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

