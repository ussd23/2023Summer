#pragma once
#include "Component.h"
#include "DXHeader.h"

class GameObject;
class Transform;

class ObjectMove : public Component
{
protected:
	Transform*		m_Transform;
	float			m_Speed;

public:
	void Start() override;
	void Update() override;

	SerializeFunction(ObjectMove) {}
};

