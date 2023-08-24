//-----------------------------------------------------------------------------
// File: CameraMove
//
// Desc: ī�޶��� ��Ŀ�� ������ ���� ��ũ��Ʈ
//
//		[Variables]
//		- m_Camera: ������Ʈ�� Camera ������Ʈ
//		- m_LerpT: Lerp �μ� �� ����
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

