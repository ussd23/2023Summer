#include "Scripts.h"

PlayerMove* PlayerMove::player = nullptr;

PlayerMove::PlayerMove(float p_Speed)
{
    m_Speed = p_Speed;
    if (player == nullptr) player = this;
}

void PlayerMove::Start()
{
    m_Transform = GetComponentFromObject(gameObject, Transform);
}

void PlayerMove::Update()
{
    if (m_Transform == nullptr) return;

    Vector3 temp = Vector3(0, 0, 0);
    float length;

    if (GetInputBuffer(g_keyhold, 'A')) temp.x -= 1;
    if (GetInputBuffer(g_keyhold, 'D')) temp.x += 1;
    if (GetInputBuffer(g_keyhold, 'W')) temp.z += 1;
    if (GetInputBuffer(g_keyhold, 'S')) temp.z -= 1;

    if (GetInputBuffer(g_keyhold, 'Q')) m_Transform->m_Rotation.y -= (90 * Time::deltaTime);
    if (GetInputBuffer(g_keyhold, 'E')) m_Transform->m_Rotation.y += (90 * Time::deltaTime);
    if (GetInputBuffer(g_keyhold, 'R')) m_Transform->m_Scale *= 1.01f;
    if (GetInputBuffer(g_keyhold, 'F')) m_Transform->m_Scale /= 1.01f;

    length = sqrt((fabs(temp.x) * fabs(temp.x) + fabs(temp.z) * fabs(temp.z)));
    if (length == 0.f) return;

    m_Transform->m_Position.x += (temp.x / length) * Time::deltaTime * m_Speed;
    m_Transform->m_Position.z += (temp.z / length) * Time::deltaTime * m_Speed;

    if (m_Transform->m_Position.x > 30) m_Transform->m_Position.x = 30;
    if (m_Transform->m_Position.x < -30) m_Transform->m_Position.x = -30;
    if (m_Transform->m_Position.z > 20) m_Transform->m_Position.z = 20;
    if (m_Transform->m_Position.z < -20) m_Transform->m_Position.z = -20;
}

void PlayerMove::OnMouseDown()
{
    MessageBox(NULL, "OnMouseDown() ½ÇÇàµÊ", "PlayerMove", MB_OK);
}

void PlayerMove::OnTriggerStay(Collider* _collider)
{
    m_isTriggered = true;
}

void PlayerMove::OnTriggerExit(Collider* _collider)
{
    m_isTriggered = false;
}