//-----------------------------------------------------------------------------
// File: Raycast
//
// Desc: Raycast�� ���õ� ���
//
//		[Variables]
//		- m_StartPt: ������ ���� ����
//		- m_Direction: ������ ���� ����
//
//		[Functions]
//      - ScreenToWorld: ���콺 �������� ȭ��� ��ġ���� ����� ��ġ�� ���ϴ� ����
//						 �� ����� ���� ������ ������ ���Ͽ� Raycast Ÿ������ ��ȯ
//      - IsPicked: Raycast�� ���� ������ ���⿡ �ش��ϴ� ������ Collider�� �浹��
//					�� ���� ���θ� ��ȯ
//      - IntersectTri: Raycast�� ���� ������ ���⿡ �ش��ϴ� ������ ����� ��ǥ
//						�� ���� �մ� ����� �浹�ϴ� ���� ���θ� ��ȯ
//-----------------------------------------------------------------------------

#pragma once
#include "DXHeader.h"
#include "StandardLibrary.h"

class BoxCollider;
class SphereCollider;

class Raycast
{
protected:
	Vector3			m_StartPt = Vector3(0.f, 0.f, 0.f);
	Vector3			m_Direction = Vector3(0.f, 0.f, 0.f);

public:
	static Raycast ScreenToWorld(const Vector2& p_Position);
	bool IsPicked(BoxCollider* p_Collider);
	bool IsPicked(SphereCollider* p_Collider);
	bool IntersectTri(const Vector3& p_V0, const Vector3& p_V1, const Vector3& p_V2, Vector3& p_Result);
};

