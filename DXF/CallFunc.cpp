#include "ComponentHeader.h"

CallFunc::CallFunc(void (*func)(), int _duration) 
{
    _func = func; // 매개변수로 넘어온 함수를 저장
    duration = _duration; // 실행할 횟수 저장
}

CallFunc::CallFunc(void(*func)())
{
    _func = func; // 매개변수로 넘어온 함수를 저장
    duration = 1; // 한번만 실행
}
