#include "Scripts.h"

void ButtonTest::Start()
{
    m_Button = GetComponentFromObject(gameObject, Button);

    AddCallFN();
}

void ButtonTest::func1()
{
    MessageBox(NULL, "OnMouseDown() �����", "ButtonTest", MB_OK);
}
void ButtonTest::func2()
{
    MessageBox(NULL, "OnMouseDown() �����2", "ButtonTest2", MB_OK);
}

void ButtonTest::AddCallFN(/*ButtonTest& p_classtarget, void(*m_CallFN)()*/)
{
    if (m_Button == nullptr) return;

    //���ø� �������� ���� �޾ƿͼ� ���� �� �ְ� �Ǹ� Button ������Ʈ�� �ű��
    m_Button->m_CallFNList.push_back(SetProc(this, &ButtonTest::func1));
    m_Button->m_CallFNList.push_back(SetProc(this, &ButtonTest::func2));
}
