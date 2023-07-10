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

	Vector3			vLookatPt;
	Vector3			vEyePt;
	Vector3			vUpVec;
	float			fovRate = 1.0f;

public:
	Camera(GameObject*, Vector3);

	void Start() override;
	void Update() override;
};
