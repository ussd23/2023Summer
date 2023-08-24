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
//		- m_Sprite: ������Ʈ�� SpriteRenderer ������Ʈ
//		- m_Vertice: ������Ʈ�� VerticeRenderer ������Ʈ
//		- m_PassedTime: �ε����� ��ȭ�� �ð����� ����� �ð�
//		- m_CurrentDynamicIndex: ���� �ε����� ���� ��ȣ
// 
//		- m_IndexMin: �ڵ� �ε����� �ּ� �ε��� ��ȣ (0���� ���� �� ����)
//		- m_IndexMax: �ڵ� �ε����� �ִ� �ε��� ��ȣ
//					(Renderer�� rectsize.y - 1���� Ŭ �� ����)
//		- m_DynamicIndex: ���� �ε��� vector (size�� 0�� ��� �ڵ� �ε��� ���)
// 
//		- m_RefreshTime: �ε����� �ٲ� �ð� ����
//		- m_isVertical: ������ �ε����� ���� (false: x�� / true: y��)
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
