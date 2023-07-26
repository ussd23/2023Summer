#include "ComponentHeader.h"

void EventManager::Update()
{
    for (std::list<Event*>::iterator it = _events.begin(); it != _events.end(); )
    {
        (*it)->Update();
        if ((*it)->IsDone()) // Ƚ���� ������ Ƚ������������ �̺�Ʈ�� �����Ѵ�.
        {
            _events.erase(it++);
        }
    }
}
