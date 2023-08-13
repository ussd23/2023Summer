#include "Scripts.h"

ButtonTest::ButtonTest(Minesweeper* Sweeper) {
    MineSweeper = Sweeper;
}

void ButtonTest::func1() {
    //MessageBox(NULL, "�ʱ�ȭ", "MineSweeper", MB_OK);
    MineSweeper->InitGame(10);
}

void ButtonTest::OnMouseUp()
{
    //�ٸ� Ŭ������ �Լ��� ����ϰ� ������
    //ButtonTest test;
    //CCallBackBase* a = SetProc(test, &ButtonTest::func1);
    //a->Interpret();


    AddCallFN(); //�̰� init�̳� start�ʿ� �־ ����ɼ� �ֵ���

    m_CallFNList[0]->Interpret();
}

void ButtonTest::AddCallFN(/*ButtonTest& p_classtarget, void(*m_CallFN)()*/)
{
    //AddCallFN���� �޾ƿͼ� pushback�ϴ¹� ã��
    m_CallFNList.push_back(SetProc(this, &ButtonTest::func1));
}
