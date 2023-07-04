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
	D3DXVECTOR3			vStartPt = D3DXVECTOR3(0.f, 0.f, 0.f);
	D3DXVECTOR3			vDirection = D3DXVECTOR3(0.f, 0.f, 0.f);

public:
	static Raycast ScreenToWorld(D3DXVECTOR2);
	bool IsPicked(BoxCollider*);
	bool IsPicked(SphereCollider*);
	bool IntersectTri(D3DXVECTOR3&, D3DXVECTOR3&, D3DXVECTOR3&, D3DXVECTOR3&);
};

