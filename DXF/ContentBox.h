#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class ContentBox : public Component
{
public:
	void Start() override;

	SerializeFunction(ContentBox) {}
};

