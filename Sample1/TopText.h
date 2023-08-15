#pragma once
#include "Component.h"

class GameObject;
class TextRenderer;
class Camera;

class TopText : public Component
{
protected:
	TextRenderer* m_Text;
	GameObject* m_Player;
	Camera* m_Camera;

public:
	void Start() override;
	void Update() override;

	SerializeFunction(TopText) {}
	DeserializeFunction() {}
};

