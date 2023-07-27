#include "Scripts.h"
#include "CallBack.h"

void ButtonTest::func1()
{
    MessageBox(NULL, "OnMouseDown() �����", "ButtonTest", MB_OK);
}
void ButtonTest::func2()
{
    MessageBox(NULL, "OnMouseDown() �����2", "ButtonTest2", MB_OK);
}

void ButtonTest::OnMouseDown()
{
    //�ٸ� Ŭ������ �Լ��� ����ϰ� ������
    //ButtonTest test;
    //CCallBackBase* a = SetProc(test, &ButtonTest::func1);
    //a->Interpret();


    AddCallFN(); //�̰� init�̳� start�ʿ� �־ ����ɼ� �ֵ���

    m_CallFNList[0]->Interpret();
    m_CallFNList[1]->Interpret();
}

void ButtonTest::AddCallFN(/*ButtonTest& p_classtarget, void(*m_CallFN)()*/)
{
    //AddCallFN���� �޾ƿͼ� pushback�ϴ¹� ã��
    m_CallFNList.push_back(SetProc(*this, &ButtonTest::func1));
    m_CallFNList.push_back(SetProc(*this, &ButtonTest::func2));

}
