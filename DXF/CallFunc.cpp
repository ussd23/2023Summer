#include "ComponentHeader.h"

CallFunc::CallFunc(void (*p_Func)(), int p_Duration)
{
    m_Func = p_Func; // 매개변수로 넘어온 함수를 저장
    duration = p_Duration; // 실행할 횟수 저장
}

CallFunc::CallFunc(void(*p_Func)())
{
    m_Func = p_Func; // 매개변수로 넘어온 함수를 저장
    duration = 1; // 한번만 실행
}
