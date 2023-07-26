#include "ComponentHeader.h"

CallFunc::CallFunc(void (*func)(), int _duration) 
{
    _func = func; // �Ű������� �Ѿ�� �Լ��� ����
    duration = _duration; // ������ Ƚ�� ����
}

CallFunc::CallFunc(void(*func)())
{
    _func = func; // �Ű������� �Ѿ�� �Լ��� ����
    duration = 1; // �ѹ��� ����
}
