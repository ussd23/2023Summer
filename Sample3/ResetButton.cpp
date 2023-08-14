#include "Scripts.h"

ResetButton::ResetButton(Minesweeper* Sweeper, int Index) {
    MineSweeper = Sweeper;
    this->Index = Index;
}

void ResetButton::func1() {
    //MessageBox(NULL, "1초기화", "MineSweeper", MB_OK);
    MineSweeper->InitGame(5);
}
void ResetButton::func2() {
    //MessageBox(NULL, "2초기화", "MineSweeper", MB_OK);
    MineSweeper->InitGame(10);
}
void ResetButton::func3() {
    //MessageBox(NULL, "3초기화", "MineSweeper", MB_OK);
    MineSweeper->InitGame(20);
}

void ResetButton::OnMouseUp() {
    //다른 클래스의 함수를 사용하고 싶을때
    //ButtonTest test;
    //CCallBackBase* a = SetProc(test, &ButtonTest::func1);
    //a->Interpret();


    AddCallFN(); //이걸 init이나 start쪽에 넣어서 실행될수 있도록
    m_CallFNList[Index]->Interpret();
}

void ResetButton::AddCallFN(/*ButtonTest& p_classtarget, void(*m_CallFN)()*/)
{
    //AddCallFN인자 받아와서 pushback하는법 찾기
    m_CallFNList.push_back(SetProc(this, &ResetButton::func1));
    m_CallFNList.push_back(SetProc(this, &ResetButton::func2));
    m_CallFNList.push_back(SetProc(this, &ResetButton::func3));
}
