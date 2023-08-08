#include "Scripts.h"

void BtnText::Start()
{
    m_Text = "Text";
    m_TextRender = GetComponentFromObject(gameObject, TextRenderer);
}

void BtnText::Update()
{
    if (m_TextRender == nullptr) return;

    stringstream temp;
    //temp << fixed << setprecision(2) << "[FPS: " << Time::framePerSec << " / AvgFPS: " << Time::avgFrame << "]\n"\
    //    << "W/A/S/D: �̵�, Q/E: ȸ��, R/F: Ȯ��/���\n[" << (camera->fovRate * 100)\
    //    << "%] ���콺 ��: ����/�ܾƿ�, ��Ŭ��: ī�޶� ��Ŀ��\n�� �ؽ�Ʈ Ȥ�� �÷��̾� ������Ʈ�� Ŭ���ϸ� �޽����ڽ� ���";
    temp << m_Text;

    m_TextRender->m_Text = temp.str();
}

void BtnText::SetText(string p_Text)
{
    m_Text = p_Text;
}

