#include "ComponentHeader.h"

void EventManager::Update()
{
    for (std::list<Event*>::iterator iter = m_Events.begin(); iter != m_Events.end(); )
    {
        (*iter)->Update();
        if ((*iter)->IsDone()) // 횟수가 지정한 횟수랑같아지면 이벤트를 삭제한다.
        {
            m_Events.erase(iter++);
        }
    }
}
