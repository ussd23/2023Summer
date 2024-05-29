#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"
#include "Collider2D.h"

class SphereCollider2D : public Collider2D
{
public:
	float		m_Radius;

public:
	SphereCollider2D(const float& p_Radius);
	SphereCollider2D(const float& p_Radius, bool p_isPassive);
	SphereCollider2D(const float& p_Radius, bool p_isPassive, bool p_isFixedChecking);
	SphereCollider2D(const float& p_Radius, bool p_isPassive, bool p_isFixedChecking, float p_CheckTime);

	void Update() override;

	SerializeFunction(SphereCollider2D)
	{
		Serialize(m_Radius);
		Serialize(m_isPassive);
		Serialize(m_isFixedChecking);
		Serialize(m_CheckTime);
	}
};

