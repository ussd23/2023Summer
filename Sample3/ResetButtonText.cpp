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
    //    << "W/A/S/D: 이동, Q/E: 회전, R/F: 확대/축소\n[" << (camera->fovRate * 100)\
    //    << "%] 마우스 휠: 줌인/줌아웃, 우클릭: 카메라 포커스\n이 텍스트 혹은 플레이어 오브젝트를 클릭하면 메시지박스 출력";
    temp << m_Text;

    m_TextRender->m_Text = temp.str();
    m_TextRender->m_Color = D3DCOLOR(0xff000000);
}

void ResetButtonText::SetText(string p_Text)
{
    m_Text = p_Text;
}

