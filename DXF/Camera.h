//-----------------------------------------------------------------------------
// File: Camera
//
// Desc: 카메라 설정 컴포넌트
//
//		[Variables]
//		- main: 메인 카메라
// 
//		- m_Transform: 오브젝트의 Transform 컴포넌트
//		- m_LookatPt: 카메라의 포커스 좌표
//		- m_EyePt: 카메라의 위치 (오브젝트의 Transform의 위치로 Update됨)
//		- m_FovRate: 카메라의 fov 값
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"
#include "DXHeader.h"

class Camera : public Component
{
public:
	static Camera*	main;

	Transform*		m_Transform;
	Vector3			m_LookatPt;
	Vector3			m_UpVec;
	float			m_FovRate = 1.0f;

public:
	Camera(const Vector3& p_Lookat);
	~Camera();

	void Awake() override;
	void Start() override;

	SerializeFunction(Camera)
	{
		Serialize(m_LookatPt);
	}
	DeserializeFunction()
	{
		Deserialize(m_LookatPt);
	}
};
