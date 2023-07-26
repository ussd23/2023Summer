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
    std::list<Event*> _events; // ���� �̺�Ʈ�� ����
public:
    void Instance(CallFunc* func) // �̺�Ʈ�� �־��� �Լ�
    {
        _events.emplace_back(func);
    }

    void Update();
};

