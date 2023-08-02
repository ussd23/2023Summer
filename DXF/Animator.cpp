#include "ComponentHeader.h"

AnimationInfo::AnimationInfo(Vector2 _index, float _time)
{
	index = _index;
	time = _time;
}

Animator::Animator(float p_RefreshTime)
	: Animator(0, MAXINT, p_RefreshTime, false) {}

Animator::Animator(int p_IndexMax, float p_RefreshTime)
	: Animator(0, p_IndexMax, p_RefreshTime, false) {}

Animator::Animator(int p_IndexMin, int p_IndexMax, float p_RefreshTime)
	: Animator(p_IndexMin, p_IndexMax, p_RefreshTime, false) {}

Animator::Animator(int p_IndexMin, int p_IndexMax, float p_RefreshTime, bool p_isVertical)
{
	m_IndexMin = p_IndexMin;
	if (m_IndexMin < 0) p_IndexMin = 0;
	m_IndexMax = p_IndexMax;
	m_RefreshTime = p_RefreshTime;
	m_isVertical = p_isVertical;
}

Animator::Animator(vector<AnimationInfo> p_DynamicIndex)
{
	m_DynamicIndex = p_DynamicIndex;
}

void Animator::Start()
{
	m_Vertice = GetComponentFromObject(gameObject, VerticeRenderer);
	m_Sprite = GetComponentFromObject(gameObject, SpriteRenderer);

	if (m_isVertical)
	{
		if (m_Vertice != nullptr)
		{
			if (m_IndexMax > m_Vertice->m_RectSize.x - 1) m_IndexMax = m_Vertice->m_RectSize.x - 1;
		}

		if (m_Sprite != nullptr)
		{
			if (m_IndexMax > m_Sprite->m_RectSize.x - 1) m_IndexMax = m_Sprite->m_RectSize.x - 1;
		}
	}
	else
	{
		if (m_Vertice != nullptr)
		{
			if (m_IndexMax > m_Vertice->m_RectSize.y - 1) m_IndexMax = m_Vertice->m_RectSize.y - 1;
		}

		if (m_Sprite != nullptr)
		{
			if (m_IndexMax > m_Sprite->m_RectSize.y - 1) m_IndexMax = m_Sprite->m_RectSize.y - 1;
		}
	}
}

void Animator::Update()
{
	m_PassedTime += Time::deltaTime;

	if (m_DynamicIndex.size() > 0)
	{
		while (true)
		{
			if (m_PassedTime < m_DynamicIndex[m_CurrentDynamicIndex].time) return;

			m_PassedTime -= m_DynamicIndex[m_CurrentDynamicIndex].time;

			if (++m_CurrentDynamicIndex >= m_DynamicIndex.size())
			{
				m_CurrentDynamicIndex = 0;
			}

			if (m_Vertice != nullptr)
			{
				m_Vertice->m_RectIndex = m_DynamicIndex[m_CurrentDynamicIndex].index;

				if (m_Vertice->m_RectIndex.x < 0) m_Vertice->m_RectIndex.x = 0;
				else if (m_Vertice->m_RectIndex.x > m_Vertice->m_RectSize.x - 1) m_Vertice->m_RectIndex.x = m_Vertice->m_RectSize.x - 1;
				if (m_Vertice->m_RectIndex.y < 0) m_Vertice->m_RectIndex.y = 0;
				else if (m_Vertice->m_RectIndex.y > m_Vertice->m_RectSize.y - 1) m_Vertice->m_RectIndex.y = m_Vertice->m_RectSize.y - 1;
			}

			if (m_Sprite != nullptr)
			{
				m_Sprite->m_RectIndex = m_DynamicIndex[m_CurrentDynamicIndex].index;

				if (m_Sprite->m_RectIndex.x < 0) m_Sprite->m_RectIndex.x = 0;
				else if (m_Sprite->m_RectIndex.x > m_Sprite->m_RectSize.x - 1) m_Sprite->m_RectIndex.x = m_Sprite->m_RectSize.x - 1;
				if (m_Sprite->m_RectIndex.y < 0) m_Sprite->m_RectIndex.y = 0;
				else if (m_Sprite->m_RectIndex.y > m_Sprite->m_RectSize.y - 1) m_Sprite->m_RectIndex.y = m_Sprite->m_RectSize.y - 1;
			}
		}
	}
	else
	{
		while (true)
		{
			if (m_PassedTime < m_RefreshTime) return;

			m_PassedTime -= m_RefreshTime;

			if (m_Vertice != nullptr)
			{
				if (m_isVertical)
				{
					m_Vertice->m_RectIndex.y += 1;
					if (m_Vertice->m_RectIndex.y > m_IndexMax) m_Vertice->m_RectIndex.y = m_IndexMin;
				}
				else
				{
					m_Vertice->m_RectIndex.x += 1;
					if (m_Vertice->m_RectIndex.x > m_IndexMax) m_Vertice->m_RectIndex.x = m_IndexMin;
				}
			}

			if (m_Sprite != nullptr)
			{
				if (m_isVertical)
				{
					m_Sprite->m_RectIndex.y += 1;
					if (m_Sprite->m_RectIndex.y > m_IndexMax) m_Sprite->m_RectIndex.y = m_IndexMin;
				}
				else
				{
					m_Sprite->m_RectIndex.x += 1;
					if (m_Sprite->m_RectIndex.x > m_IndexMax) m_Sprite->m_RectIndex.x = m_IndexMin;
				}
			}
		}
	}
}