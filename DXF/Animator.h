//-----------------------------------------------------------------------------
// File: Animator
//
// Desc: ��������Ʈ ������ ���� ������Ʈ
//
//		[Variables]
//		- sprite: ������Ʈ�� SpriteRenderer ������Ʈ
//		- vertice: ������Ʈ�� VerticeRenderer ������Ʈ
//		- passedTime: �ε����� ��ȭ�� �ð����� ����� �ð�
//		- indexMin: �ּ� �ε��� ��ȣ (0���� ���� �� ����)
//		- indexMax: �ִ� �ε��� ��ȣ (Renderer�� rectsize.y - 1���� Ŭ �� ����)
//		- refreshTime: �ε����� �ٲ� �ð� ����
//		- isDown: ������ �ε����� ���� (false: x�� / true: y��)
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class SpriteRenderer;
class VerticeRenderer;

class Animator : public Component
{
protected:
	SpriteRenderer*		sprite;
	VerticeRenderer*	vertice;
	FLOAT				passedTime = 0.f;

public:
	int					indexMin;
	int					indexMax;
	float				refreshTime;
	bool				isDown;

public:
	Animator(int, float);
	Animator(int, int, float);
	Animator(int, int, float, bool);

	void Start() override;
	void Update() override;
};
