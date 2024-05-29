#pragma once
#include "Collider.h"

class RectTransform;
class BoxCollider2D;
class SphereCollider2D;

class Collider2D : public Collider
{
public:
	RectTransform*	m_RectTransform;

protected:
	static bool GetSeparatingPlane(Vector2 p_RPos, Vector2 p_Plane, BoxCollider2D* p_Col1, BoxCollider2D* p_Col2);

public:
	static bool CollisionCheckBtoB(BoxCollider2D* p_Col1, BoxCollider2D* p_Col2);
	static bool CollisionCheckBtoS(BoxCollider2D* p_Col1, SphereCollider2D* p_Col2);
	static bool CollisionCheckStoS(SphereCollider2D* p_Col1, SphereCollider2D* p_Col2);

	void Start() override;
};

