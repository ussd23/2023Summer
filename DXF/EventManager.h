#pragma once
#include "DXHeader.h"
#include "StandardLibrary.h"

class Event
{
public:
    int duration; // 소요 시간
    int elapse = 0; // 경과 시간

    virtual void Update() = 0;
    bool IsDone()
    {
        return elapse >= duration;
    }
};

class CallFunc;

class EventManager
{
public:
    std::list<Event*> _events; // 모은 이벤트를 저장
public:
    void Instance(CallFunc* func) // 이벤트를 넣어줄 함수
    {
        _events.emplace_back(func);
    }

    void Update();
};

