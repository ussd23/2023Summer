#include "Scripts.h"

BubbleManager* BubbleManager::m_BubbleManager = nullptr;

void BubbleManager::Awake()
{
    if (m_BubbleManager == nullptr) m_BubbleManager = this;
}
