//-----------------------------------------------------------------------------
// File: Animator
//
// Desc: ��������Ʈ ������ ���� ������Ʈ
// 
//		[Class]
//		- AnimationInfo: �ִϸ��̼� ������ �����ϴ� Ŭ����
//			- index: �ش�Ǵ� �ε���
//			- time: �ش� �ε����� ������ �ð�
//
//		[Variables]
//		- sprite: ������Ʈ�� SpriteRenderer ������Ʈ
//		- vertice: ������Ʈ�� VerticeRenderer ������Ʈ
//		- passedTime: �ε����� ��ȭ�� �ð����� ����� �ð�
//		- currentdynamicIndex: ���� �ε����� ���� ��ȣ
// 
//		- indexMin: �ڵ� �ε����� �ּ� �ε��� ��ȣ (0���� ���� �� ����)
//		- indexMax: �ڵ� �ε����� �ִ� �ε��� ��ȣ
//					(Renderer�� rectsize.y - 1���� Ŭ �� ����)
//		- dynamicIndex: ���� �ε��� vector (size�� 0�� ��� �ڵ� �ε��� ���)
// 
//		- refreshTime: �ε����� �ٲ� �ð� ����
//		- isVertical: ������ �ε����� ���� (false: x�� / true: y��)
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class SpriteRenderer;
class VerticeRenderer;

class AnimationInfo
{
public:
	Vector2					index;
	float					time;
};

class Animator : public Component
{
protected:
	SpriteRenderer*			sprite = nullptr;
	VerticeRenderer*		vertice = nullptr;
	FLOAT					passedTime = 0.f;
	int						currentdynamicIndex = 0;

public:
	int						indexMin;
	int						indexMax;
	vector<AnimationInfo>	dynamicIndex;

	float					refreshTime;
	bool					isVertical;

public:
	Animator(float);
	Animator(int, float);
	Animator(int, int, float);
	Animator(int, int, float, bool);
	Animator(vector<AnimationInfo>);

	void Start() override;
	void Update() override;
};
