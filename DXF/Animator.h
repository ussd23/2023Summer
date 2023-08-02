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
//		- m_Sprite: 오브젝트의 SpriteRenderer 컴포넌트
//		- m_Vertice: 오브젝트의 VerticeRenderer 컴포넌트
//		- m_PassedTime: 인덱스가 변화된 시간부터 경과한 시간
//		- m_CurrentDynamicIndex: 동적 인덱스의 현재 번호
// 
//		- m_IndexMin: 자동 인덱스의 최소 인덱스 번호 (0보다 작을 수 없음)
//		- m_IndexMax: 자동 인덱스의 최대 인덱스 번호
//					(Renderer의 rectsize.y - 1보다 클 수 없음)
//		- m_DynamicIndex: 동적 인덱스 vector (size가 0일 경우 자동 인덱스 사용)
// 
//		- m_RefreshTime: 인덱스를 바꿀 시간 차이
//		- m_isVertical: 변경할 인덱스의 방향 (false: x축 / true: y축)
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class SpriteRenderer;
class VerticeRenderer;

class AnimationInfo : public Serializable
{
public:
	Vector2					index;
	float					time;

public:
	AnimationInfo(Vector2 _index, float _time);

	SerializeFunction(AnimationInfo)
	{
		Serialize(index);
		Serialize(time);
	}
	DeserializeFunction()
	{
		Deserialize(index);
		Deserialize(time);
	}
};

class Animator : public Component
{
protected:
	SpriteRenderer*			m_Sprite = nullptr;
	VerticeRenderer*		m_Vertice = nullptr;
	FLOAT					m_PassedTime = 0.f;
	int						m_CurrentDynamicIndex = 0;

public:
	int						m_IndexMin;
	int						m_IndexMax;
	vector<AnimationInfo>	m_DynamicIndex;

	float					m_RefreshTime;
	bool					m_isVertical;

public:
	Animator(float p_RefreshTime);
	Animator(int p_IndexMax, float p_RefreshTime);
	Animator(int p_IndexMin, int p_IndexMax, float p_RefreshTime);
	Animator(int p_IndexMin, int p_IndexMax, float p_RefreshTime, bool p_isVertical);
	Animator(vector<AnimationInfo> p_DynamicIndex);

	void Start() override;
	void Update() override;

	SerializeFunction(Animator)
	{
		Serialize(m_IndexMin);
		Serialize(m_IndexMax);
		Serialize(m_RefreshTime);
		Serialize(m_isVertical);
		SuperVectorSerialize(m_DynamicIndex);
	}
	DeserializeFunction()
	{
		Deserialize(m_IndexMin);
		Deserialize(m_IndexMax);
		Deserialize(m_RefreshTime);
		Deserialize(m_isVertical);
		SuperVectorDeserialize(m_DynamicIndex);
	}
};
