#include "ComponentHeader.h"

bool Renderer::Compare(Renderer* _r1, Renderer* _r2)
{
	return _r1->distance < _r2->distance;
}