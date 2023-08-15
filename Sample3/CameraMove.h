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
	class Minesweeper* Mine_Sweeper;
	Camera*		m_Camera;
	float		m_LerpT = 5.f;

public:
	CameraMove(Minesweeper* Sweeper);

	void Start() override;
	void Update() override;

	SerializeFunction(CameraMove)
	{
		Serialize(m_LerpT);
	}
	DeserializeFunction()
	{
		Deserialize(m_LerpT);
	}
};

