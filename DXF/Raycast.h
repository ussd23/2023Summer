//-----------------------------------------------------------------------------
// File: Raycast
//
// Desc: Raycast�� ���õ� ���
//
//		[Variables]
//		- vStartPt: ������ ���� ����
//		- vDirection: ������ ���� ����
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
	Vector3			vStartPt = Vector3(0.f, 0.f, 0.f);
	Vector3			vDirection = Vector3(0.f, 0.f, 0.f);

public:
	static Raycast ScreenToWorld(const Vector2&);
	bool IsPicked(BoxCollider*);
	bool IsPicked(SphereCollider*);
	bool IntersectTri(const Vector3&, const Vector3&, const Vector3&, Vector3&);
};

