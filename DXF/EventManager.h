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
    std::list<Event*> m_Events; // 모은 이벤트를 저장
public:
    void Instance(CallFunc* p_Func) // 이벤트를 넣어줄 함수
    {
        m_Events.emplace_back(p_Func);
    }

    void Update();
};

//다른걸로 대체해서 안쓸거같은데 혹시모르니 일단 남김