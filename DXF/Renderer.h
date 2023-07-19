#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class Renderer : public Component
{
public:
	float m_Distance = 0.f;

protected:
	virtual void PreRender() = 0;

public:
	virtual void Render() = 0;
	static bool Compare(Renderer* p_R1, Renderer* p_R2);
};

