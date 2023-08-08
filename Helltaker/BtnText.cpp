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
    //    << "W/A/S/D: 이동, Q/E: 회전, R/F: 확대/축소\n[" << (camera->fovRate * 100)\
    //    << "%] 마우스 휠: 줌인/줌아웃, 우클릭: 카메라 포커스\n이 텍스트 혹은 플레이어 오브젝트를 클릭하면 메시지박스 출력";
    temp << m_Text;

    m_TextRender->m_Text = temp.str();
}

void BtnText::SetText(string p_Text)
{
    m_Text = p_Text;
}

