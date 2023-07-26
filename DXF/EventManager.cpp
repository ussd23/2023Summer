#include "ComponentHeader.h"

void EventManager::Update()
{
    for (std::list<Event*>::iterator it = _events.begin(); it != _events.end(); )
    {
        (*it)->Update();
        if ((*it)->IsDone()) // 횟수가 지정한 횟수랑같아지면 이벤트를 삭제한다.
        {
            _events.erase(it++);
        }
    }
}
