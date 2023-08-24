#include "Scripts.h"

ResetButtonText::ResetButtonText(int Index) {
    switch (Index) {
        case 0:
            m_Text = "Easy";
            break;
        case 1:
            m_Text = "Normal";
            break;
        case 2:
            m_Text = "Hard";
            break;
    }
}

void ResetButtonText::Start()
{
    
    m_TextRender = GetComponentFromObject(gameObject, TextRenderer);
}

void ResetButtonText::Update()
{
    if (m_TextRender == nullptr) return;

    stringstream temp;
    //temp << fixed << setprecision(2) << "[FPS: " << Time::framePerSec << " / AvgFPS: " << Time::avgFrame << "]\n"\
    //    << "W/A/S/D: �̵�, Q/E: ȸ��, R/F: Ȯ��/���\n[" << (camera->fovRate * 100)\
    //    << "%] ���콺 ��: ����/�ܾƿ�, ��Ŭ��: ī�޶� ��Ŀ��\n�� �ؽ�Ʈ Ȥ�� �÷��̾� ������Ʈ�� Ŭ���ϸ� �޽����ڽ� ���";
    temp << m_Text;

    m_TextRender->m_Text = temp.str();
    m_TextRender->m_Color = D3DCOLOR(0xff000000);
}

void ResetButtonText::SetText(string p_Text)
{
    m_Text = p_Text;
}

