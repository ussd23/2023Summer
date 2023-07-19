#include "ComponentHeader.h"

bool Renderer::Compare(Renderer* p_R1, Renderer* p_R2)
{
	return p_R1->m_Distance < p_R2->m_Distance;
}