#include "ComponentHeader.h"

CallFunc::CallFunc(void (*p_Func)(), int p_Duration)
{
    m_Func = p_Func; // �Ű������� �Ѿ�� �Լ��� ����
    duration = p_Duration; // ������ Ƚ�� ����
}

CallFunc::CallFunc(void(*p_Func)())
{
    m_Func = p_Func; // �Ű������� �Ѿ�� �Լ��� ����
    duration = 1; // �ѹ��� ����
}
