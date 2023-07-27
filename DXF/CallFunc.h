#pragma once
#include "EventManager.h"

class CallFunc : public Event
{
public:
    void (*m_Func)(); // 함수포인터를 맴버변수로 가진다.
public:
    CallFunc(void (*p_Func)(), int p_Duration);
    CallFunc(void (*p_Func)());

    virtual void Update() override
    {
        m_Func();
        elapse += 1;
        return;
    }
};

//다른걸로 대체해서 안쓸거같은데 혹시모르니 일단 남김