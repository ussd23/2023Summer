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
//		- isVertical: ������ �ε����� ���� (false: x�� / true: y��)
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
	SpriteRenderer*		sprite = nullptr;
	VerticeRenderer*	vertice = nullptr;
	FLOAT				passedTime = 0.f;

public:
	int					indexMin;
	int					indexMax;
	float				refreshTime;
	bool				isVertical;

public:
	Animator(float);
	Animator(int, float);
	Animator(int, int, float);
	Animator(int, int, float, bool);

	void Start() override;
	void Update() override;
};
