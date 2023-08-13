#include "Scripts.h"

ButtonTest::ButtonTest(Minesweeper* Sweeper) {
    MineSweeper = Sweeper;
}

void ButtonTest::func1() {
    //MessageBox(NULL, "초기화", "MineSweeper", MB_OK);
    MineSweeper->InitGame(10);
}

void ButtonTest::OnMouseUp()
{
    //다른 클래스의 함수를 사용하고 싶을때
    //ButtonTest test;
    //CCallBackBase* a = SetProc(test, &ButtonTest::func1);
    //a->Interpret();


    AddCallFN(); //이걸 init이나 start쪽에 넣어서 실행될수 있도록

    m_CallFNList[0]->Interpret();
}

void ButtonTest::AddCallFN(/*ButtonTest& p_classtarget, void(*m_CallFN)()*/)
{
    //AddCallFN인자 받아와서 pushback하는법 찾기
    m_CallFNList.push_back(SetProc(this, &ButtonTest::func1));
}
