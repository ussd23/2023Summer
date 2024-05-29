#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"
#include "Collider2D.h"

class RectTransform;

class BoxCollider2D : public Collider2D
{
public:
	Vector2			m_Size;
	Vector2			m_HalfSize;
	Vector2			m_AxisX;
	Vector2			m_AxisY;

public:
	BoxCollider2D(const Vector2& p_Size);
	BoxCollider2D(const Vector2& p_Size, bool p_isPassive);
	BoxCollider2D(const Vector2& p_Size, bool p_isPassive, bool p_isFixedChecking);
	BoxCollider2D(const Vector2& p_Size, bool p_isPassive, bool p_isFixedChecking, float p_CheckTime);

	void PreUpdate() override;
	void Update() override;

	SerializeFunction(BoxCollider2D)
	{
		Serialize(m_Size);
		Serialize(m_isPassive);
		Serialize(m_isFixedChecking);
		Serialize(m_CheckTime);
	}
};
