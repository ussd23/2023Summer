#include "ComponentHeader.h"

void EventManager::Update()
{
    for (std::list<Event*>::iterator iter = m_Events.begin(); iter != m_Events.end(); )
    {
        (*iter)->Update();
        if ((*iter)->IsDone()) // Ƚ���� ������ Ƚ������������ �̺�Ʈ�� �����Ѵ�.
        {
            m_Events.erase(iter++);
        }
    }
}
