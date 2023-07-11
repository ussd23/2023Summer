//-----------------------------------------------------------------------------
// File: Animator
//
// Desc: 스프라이트 렌더를 위한 컴포넌트
//
//		[Variables]
//		- sprite: 오브젝트의 SpriteRenderer 컴포넌트
//		- vertice: 오브젝트의 VerticeRenderer 컴포넌트
//		- passedTime: 인덱스가 변화된 시간부터 경과한 시간
//		- indexMin: 최소 인덱스 번호 (0보다 작을 수 없음)
//		- indexMax: 최대 인덱스 번호 (Renderer의 rectsize.y - 1보다 클 수 없음)
//		- refreshTime: 인덱스를 바꿀 시간 차이
//		- isVertical: 변경할 인덱스의 방향 (false: x축 / true: y축)
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
