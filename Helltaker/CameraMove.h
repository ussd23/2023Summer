//-----------------------------------------------------------------------------
// File: CameraMove
//
// Desc: 카메라의 포커스 변경을 위한 스크립트
//
//		[Variables]
//		- m_Camera: 오브젝트의 Camera 컴포넌트
//		- m_LerpT: Lerp 인수 값 배율
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"
#include "DXHeader.h"

class GameObject;
class Camera;

class CameraMove : public Component
{
protected:
	Camera*		m_Camera;
	float		m_LerpT = 5.f;

public:
	void Start() override;
	void Update() override;

	SerializeFunction(CameraMove)
	{
	}
	DeserializeFunction()
	{
	}
};

