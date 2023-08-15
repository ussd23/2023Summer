#pragma once
#include "Component.h"

class GameObject;
class RectTransform;
class Collider;

class Controll : public Component
{
protected:
	RectTransform* m_RectTransform;

public:
	static Controll* m_Controll;

public:
	void Awake() override;
	void Start() override;
	void Update() override;

	SerializeFunction(Controll) {}
	DeserializeFunction() {}
};
