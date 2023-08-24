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
		Serialize(m_LerpT);
	}
	DeserializeFunction()
	{
		Deserialize(m_LerpT);
	}
};

