//-----------------------------------------------------------------------------
// File: CameraMove
//
// Desc: ī�޶��� ��Ŀ�� ������ ���� ��ũ��Ʈ
//
//		[Variables]
//		- camera: ������Ʈ�� Camera ������Ʈ
//		- LerpT: Lerp �μ� �� ����
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"
#include "DXHeader.h"

class GameObject;
class Camera;

class CameraMove : public Component
{
protected:
	Camera*		camera;
	float		LerpT = 5.f;

public:
	void Start() override;
	void Update() override;
};

