//-----------------------------------------------------------------------------
// File: Animator
//
// Desc: 스프라이트 렌더를 위한 컴포넌트
// 
//		[Class]
//		- AnimationInfo: 애니메이션 정보를 저장하는 클래스
//			- index: 해당되는 인덱스
//			- time: 해당 인덱스를 유지할 시간
//
//		[Variables]
//		- sprite: 오브젝트의 SpriteRenderer 컴포넌트
//		- vertice: 오브젝트의 VerticeRenderer 컴포넌트
//		- passedTime: 인덱스가 변화된 시간부터 경과한 시간
//		- currentdynamicIndex: 동적 인덱스의 현재 번호
// 
//		- indexMin: 자동 인덱스의 최소 인덱스 번호 (0보다 작을 수 없음)
//		- indexMax: 자동 인덱스의 최대 인덱스 번호
//					(Renderer의 rectsize.y - 1보다 클 수 없음)
//		- dynamicIndex: 동적 인덱스 vector (size가 0일 경우 자동 인덱스 사용)
// 
//		- refreshTime: 인덱스를 바꿀 시간 차이
//		- isVertical: 변경할 인덱스의 방향 (false: x축 / true: y축)
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
