#pragma once
#include "Component.h"

class GameObject;
class Transform;
class Collider;

class PlayerMove : public Component
{
protected:
	Transform*			m_Transform;
	Vector3				m_Direction;

public:
	static PlayerMove*	player;
	bool				m_isTriggered = false;
	bool				m_isLanding;
	float				m_Speed;
	float				m_AdditionTorque;
	Vector3				m_RotationTorque;

public:
	PlayerMove(float p_Speed);

	void Awake() override;
	void Start() override;
	void Update() override;
	void OnTriggerStay(Collider* p_Collider) override;
	void OnTriggerExit(Collider* p_Collider) override;

	SerializeFunction(PlayerMove)
	{
		Serialize(m_Speed);
	}
	DeserializeFunction()
	{
		Deserialize(m_Speed);
	}
};

