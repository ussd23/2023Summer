#pragma once
#include "Component.h"

class BubbleManager : public Component
{
public:
	Bubble* m_AllBubble[7][8] = {nullptr};
	static BubbleManager* m_BubbleManager;

public:
	void Awake() override;

	SerializeFunction(BubbleManager) {}
};

