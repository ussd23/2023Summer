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
        << "W/S: ����/����, A/D: ���� ȸ��, Q/E: ��ȸ ����, R/F: ���/�ϰ�";
    temp << "\n�÷��̾� ��ǥ: (" << wpos.x << ", " << wpos.y << ", " << wpos.z << ") / �ӷ�: " << playermove->m_Speed * playermove->m_AdditionTorque;
    if (playermove->m_isTriggered) temp << " (�浹��)";

    m_Text->m_Text = temp.str();
}