#include "ComponentHeader.h"

Animator::Animator(float _refreshTime)
	: Animator(MAXINT, _refreshTime) {}

Animator::Animator(int _indexMax, float _refreshTime)
	: Animator(0, _indexMax, _refreshTime) {}

Animator::Animator(int _indexMin, int _indexMax, float _refreshTime)
	: Animator(0, _indexMax, _refreshTime, false) {}

Animator::Animator(int _indexMin, int _indexMax, float _refreshTime, bool _isVertical)
{
	indexMin = _indexMin;
	if (indexMin < 0) indexMin = 0;
	indexMax = _indexMax;
	refreshTime = _refreshTime;
	isVertical = _isVertical;
}

Animator::Animator(vector<AnimationInfo> _dynamicIndex)
{
	dynamicIndex = _dynamicIndex;
}

void Animator::Start()
{
	vertice = GetComponentFromObject(gameObject, VerticeRenderer);
	sprite = GetComponentFromObject(gameObject, SpriteRenderer);

	if (isVertical)
	{
		if (vertice != nullptr)
		{
			if (indexMax > vertice->rectsize.x - 1) indexMax = vertice->rectsize.x - 1;
		}

		if (sprite != nullptr)
		{
			if (indexMax > sprite->rectsize.x - 1) indexMax = sprite->rectsize.x - 1;
		}
	}
	else
	{
		if (vertice != nullptr)
		{
			if (indexMax > vertice->rectsize.y - 1) indexMax = vertice->rectsize.y - 1;
		}

		if (sprite != nullptr)
		{
			if (indexMax > sprite->rectsize.y - 1) indexMax = sprite->rectsize.y - 1;
		}
	}
}

void Animator::Update()
{
	passedTime += Time::deltaTime;

	if (dynamicIndex.size() > 0)
	{
		if (passedTime < dynamicIndex[currentdynamicIndex].time) return;

		passedTime -= dynamicIndex[currentdynamicIndex].time;

		if (++currentdynamicIndex >= dynamicIndex.size())
		{
			currentdynamicIndex = 0;
		}

		if (vertice != nullptr)
		{
			vertice->rectindex = dynamicIndex[currentdynamicIndex].index;

			if (vertice->rectindex.x < 0) vertice->rectindex.x = 0;
			else if (vertice->rectindex.x > vertice->rectsize.x - 1) vertice->rectindex.x = vertice->rectsize.x - 1;
			if (vertice->rectindex.y < 0) vertice->rectindex.y = 0;
			else if (vertice->rectindex.y > vertice->rectsize.y - 1) vertice->rectindex.y = vertice->rectsize.y - 1;
		}

		if (sprite != nullptr)
		{
			sprite->rectindex = dynamicIndex[currentdynamicIndex].index;

			if (sprite->rectindex.x < 0) sprite->rectindex.x = 0;
			else if (sprite->rectindex.x > sprite->rectsize.x - 1) sprite->rectindex.x = sprite->rectsize.x - 1;
			if (sprite->rectindex.y < 0) sprite->rectindex.y = 0;
			else if (sprite->rectindex.y > sprite->rectsize.y - 1) sprite->rectindex.y = sprite->rectsize.y - 1;
		}

	}
	else
	{
		if (passedTime < refreshTime) return;

		passedTime -= refreshTime;

		if (vertice != nullptr)
		{
			if (isVertical)
			{
				vertice->rectindex.y += 1;
				if (vertice->rectindex.y > indexMax) vertice->rectindex.y = indexMin;
			}
			else
			{
				vertice->rectindex.x += 1;
				if (vertice->rectindex.x > indexMax) vertice->rectindex.x = indexMin;
			}
		}

		if (sprite != nullptr)
		{
			if (isVertical)
			{
				sprite->rectindex.y += 1;
				if (sprite->rectindex.y > indexMax) sprite->rectindex.y = indexMin;
			}
			else
			{
				sprite->rectindex.x += 1;
				if (sprite->rectindex.x > indexMax) sprite->rectindex.x = indexMin;
			}
		}
	}
}