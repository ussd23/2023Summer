#pragma once
#include "EventManager.h"

class CallFunc : public Event
{
public:
    void (*_func)(); // �Լ������͸� �ɹ������� ������.
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

