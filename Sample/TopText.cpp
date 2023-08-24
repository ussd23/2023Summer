#include "Scripts.h"

void TopText::Start()
{
    m_Text = GetComponentFromObject(gameObject, TextRenderer);
    m_Camera = Camera::main;
    m_Player = PlayerMove::player->gameObject;
}

void TopText::Update()
{
    if (m_Text == nullptr) return;
    if (m_Camera == nullptr) return;
    if (m_Player == nullptr) return;

    Transform* transform = GetComponentFromObject(m_Player, Transform);
    if (transform == nullptr) return;
    PlayerMove* playermove = GetComponentFromObject(m_Player, PlayerMove);
    if (playermove == nullptr) return;

    Vector3 wpos = transform->GetWorldPosition();
    Vector2 spos = Functions::WorldToScreen(transform);

    stringstream temp;
    temp << fixed << setprecision(2) << "[FPS: " << Time::framePerSec << " / AvgFPS: " << Time::avgFrame << "] / Rendered: " << Var::CullingObjects << "\n"\
        << "W/A/S/D: 이동, Q/E: 회전, R/F: 확대/축소\n[" << (m_Camera->m_FovRate * 100)\
        << "%] 마우스 휠: 줌인/줌아웃, 우클릭: 카메라 포커스\n이 텍스트 혹은 플레이어 오브젝트를 클릭하면 메시지박스 출력";
    if (playermove->m_isTriggered) temp << " (충돌중)";
    temp << "\n플레이어 좌표: 월드 (" << wpos.x << ", " << wpos.y << ", " << wpos.z << ") / 화면 (" << spos.x << ", " << spos.y << ")";

    m_Text->m_Text = temp.str();
}

void TopText::OnMouseDown()
{
    MessageBox(NULL, "OnMouseDown() 실행됨", "TopText", MB_OK);
}