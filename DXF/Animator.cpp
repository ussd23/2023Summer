#include "ComponentHeader.h"

Animator::Animator(int _indexMax, float _refreshTime)
	: Animator(0, _indexMax, _refreshTime) {}

Animator::Animator(int _indexMin, int _indexMax, float _refreshTime)
	: Animator(0, _indexMax, _refreshTime, false) {}

Animator::Animator(int _indexMin, int _indexMax, float _refreshTime, bool _isDown)
{
	indexMin = _indexMin;
	if (indexMin < 0) indexMin = 0;
	indexMax = _indexMax;
	refreshTime = _refreshTime;
	isDown = _isDown;
}

void Animator::Start()
{
	vertice = GetComponentFromObject(gameObject, VerticeRenderer);
	sprite = GetComponentFromObject(gameObject, SpriteRenderer);

	if (vertice != nullptr)
	{
		//if (indexMax > vertice->rectsize.y - 1) indexMax = vertice->rectsize.y - 1;
	}

	if (sprite != nullptr)
	{
		if (indexMax > sprite->rectsize.y - 1) indexMax = sprite->rectsize.y - 1;
	}
}

void Animator::Update()
{
	passedTime += Time::deltaTime;

	if (passedTime < refreshTime) return;

	if (vertice != nullptr)
	{

	}

	if (sprite != nullptr)
	{
		if (isDown)
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

	passedTime -= refreshTime;
}