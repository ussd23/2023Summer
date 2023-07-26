#pragma once
#include "EventManager.h"

class CallFunc : public Event
{
public:
    void (*_func)(); // 함수포인터를 맴버변수로 가진다.
public:
    CallFunc(void (*func)(), int _duration);
    CallFunc(void (*func)());

    virtual void Update() override
    {
        _func();
        elapse += 1;
        return;
    }
};

