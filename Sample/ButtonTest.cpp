#include "Scripts.h"

void ButtonTest::Start()
{
    m_Button = GetComponentFromObject(gameObject, Button);

    AddCallFN();
}

void ButtonTest::func1()
{
    MessageBox(NULL, "OnMouseDown() 실행됨", "ButtonTest", MB_OK);
}
void ButtonTest::func2()
{
    MessageBox(NULL, "OnMouseDown() 실행됨2", "ButtonTest2", MB_OK);
}

void ButtonTest::AddCallFN(/*ButtonTest& p_classtarget, void(*m_CallFN)()*/)
{
    if (m_Button == nullptr) return;

    //탬플릿 형식으로 인자 받아와서 넣을 수 있게 되면 Button 컴포넌트로 옮기기
    m_Button->m_CallFNList.push_back(SetProc(this, &ButtonTest::func1));
    m_Button->m_CallFNList.push_back(SetProc(this, &ButtonTest::func2));
}
