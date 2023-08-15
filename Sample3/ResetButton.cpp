#include "Scripts.h"

ResetButton::ResetButton(Minesweeper* Sweeper, int Index) {
    MineSweeper = Sweeper;
    this->Index = Index;
}

void ResetButton::func1() {
    //MessageBox(NULL, "1�ʱ�ȭ", "MineSweeper", MB_OK);
    MineSweeper->InitGame(5);
}
void ResetButton::func2() {
    //MessageBox(NULL, "2�ʱ�ȭ", "MineSweeper", MB_OK);
    MineSweeper->InitGame(10);
}
void ResetButton::func3() {
    //MessageBox(NULL, "3�ʱ�ȭ", "MineSweeper", MB_OK);
    MineSweeper->InitGame(20);
}

void ResetButton::OnMouseUp() {
    //�ٸ� Ŭ������ �Լ��� ����ϰ� ������
    //ButtonTest test;
    //CCallBackBase* a = SetProc(test, &ButtonTest::func1);
    //a->Interpret();


    AddCallFN(); //�̰� init�̳� start�ʿ� �־ ����ɼ� �ֵ���
    m_CallFNList[Index]->Interpret();
}

void ResetButton::AddCallFN(/*ButtonTest& p_classtarget, void(*m_CallFN)()*/)
{
    //AddCallFN���� �޾ƿͼ� pushback�ϴ¹� ã��
    m_CallFNList.push_back(SetProc(this, &ResetButton::func1));
    m_CallFNList.push_back(SetProc(this, &ResetButton::func2));
    m_CallFNList.push_back(SetProc(this, &ResetButton::func3));
}
