//-----------------------------------------------------------------------------
// File: Camera
//
// Desc: 카메라 설정 컴포넌트
//
//		[Variables]
//		- transform: 오브젝트의 Transform 컴포넌트
//		- main: 메인 카메라
//		- vLookatPt: 카메라의 포커스 좌표
//		- vEyePt: 카메라의 위치 (오브젝트의 Transform의 위치로 Update됨)
//		- fovRate: 카메라의 fov 값
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
