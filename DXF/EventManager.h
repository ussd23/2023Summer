#pragma once
#include "DXHeader.h"
#include "StandardLibrary.h"

class Event
{
public:
    int duration; // �ҿ� �ð�
    int elapse = 0; // ��� �ð�

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
    std::list<Event*> m_Events; // ���� �̺�Ʈ�� ����
public:
    void Instance(CallFunc* p_Func) // �̺�Ʈ�� �־��� �Լ�
    {
        m_Events.emplace_back(p_Func);
    }

    void Update();
};

//�ٸ��ɷ� ��ü�ؼ� �Ⱦ��Ű����� Ȥ�ø𸣴� �ϴ� ����