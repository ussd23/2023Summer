#pragma once
#include "EventManager.h"

class CallFunc : public Event
{
public:
    void (*m_Func)(); // �Լ������͸� �ɹ������� ������.
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

//�ٸ��ɷ� ��ü�ؼ� �Ⱦ��Ű����� Ȥ�ø𸣴� �ϴ� ����