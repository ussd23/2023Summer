//-----------------------------------------------------------------------------
// File: Raycast
//
// Desc: Raycast와 관련된 기능
//
//		[Variables]
//		- vStartPt: 직선의 시작 지점
//		- vDirection: 직선의 진행 방향
//
//		[Functions]
//      - ScreenToWorld: 마우스 포인터의 화면상 위치에서 월드상 위치로 향하는 직선
//						 의 월드상 시작 지점과 방향을 구하여 Raycast 타입으로 반환
//      - IsPicked: Raycast의 시작 지점과 방향에 해당하는 직선에 Collider가 충돌하
//					는 지의 여부를 반환
//      - IntersectTri: Raycast의 시작 지점과 방향에 해당하는 직선에 월드상 좌표
//						세 곳을 잇는 평면이 충돌하는 지의 여부를 반환
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

