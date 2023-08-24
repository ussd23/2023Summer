//-----------------------------------------------------------------------------
// File: Camera
//
// Desc: ī�޶� ���� ������Ʈ
//
//		[Variables]
//		- main: ���� ī�޶�
// 
//		- m_Transform: ������Ʈ�� Transform ������Ʈ
//		- m_LookatPt: ī�޶��� ��Ŀ�� ��ǥ
//		- m_EyePt: ī�޶��� ��ġ (������Ʈ�� Transform�� ��ġ�� Update��)
//		- m_FovRate: ī�޶��� fov ��
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
