//-----------------------------------------------------------------------------
// File: Camera
//
// Desc: ī�޶� ���� ������Ʈ
//
//		[Variables]
//		- transform: ������Ʈ�� Transform ������Ʈ
//		- main: ���� ī�޶�
//		- vLookatPt: ī�޶��� ��Ŀ�� ��ǥ
//		- vEyePt: ī�޶��� ��ġ (������Ʈ�� Transform�� ��ġ�� Update��)
//		- fovRate: ī�޶��� fov ��
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"
#include "DXHeader.h"

class Camera : public Component
{
public:
	Transform*		transform;
	static Camera*	main;

	D3DXVECTOR3		vLookatPt;
	D3DXVECTOR3		vEyePt;
	D3DXVECTOR3		vUpVec;
	float			fovRate = 1.0f;

public:
	Camera(GameObject*, D3DXVECTOR3);

	void Start() override;
	void Update() override;
};
