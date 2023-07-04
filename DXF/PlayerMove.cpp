#include "ComponentHeader.h"

PlayerMove* PlayerMove::player = nullptr;

PlayerMove::PlayerMove(float _movespeed)
{
    movespeed = _movespeed;
    if (player == nullptr) player = this;
}

void PlayerMove::Start()
{
    transform = GetComponentFromObject(gameObject, Transform);
}

void PlayerMove::Update()
{
    if (transform == nullptr) return;

    D3DXVECTOR3 temp = D3DXVECTOR3(0, 0, 0);
    float length;

    if (GetInputBuffer(g_keyhold, 'A')) temp.x -= 1;
    if (GetInputBuffer(g_keyhold, 'D')) temp.x += 1;
    if (GetInputBuffer(g_keyhold, 'W')) temp.z += 1;
    if (GetInputBuffer(g_keyhold, 'S')) temp.z -= 1;

    if (GetInputBuffer(g_keyhold, 'Q')) transform->rotation.y -= (90 * Time::deltaTime);
    if (GetInputBuffer(g_keyhold, 'E')) transform->rotation.y += (90 * Time::deltaTime);
    if (GetInputBuffer(g_keyhold, 'R')) transform->scale *= 1.01f;
    if (GetInputBuffer(g_keyhold, 'F')) transform->scale /= 1.01f;

    length = sqrt((fabs(temp.x) * fabs(temp.x) + fabs(temp.z) * fabs(temp.z)));
    if (length == 0.f) return;

    transform->position.x += (temp.x / length) * Time::deltaTime * movespeed;
    transform->position.z += (temp.z / length) * Time::deltaTime * movespeed;

    if (transform->position.x > 30) transform->position.x = 30;
    if (transform->position.x < -30) transform->position.x = -30;
    if (transform->position.z > 20) transform->position.z = 20;
    if (transform->position.z < -20) transform->position.z = -20;
}

void PlayerMove::OnMouseClick()
{
    MessageBox(NULL, "OnMouseClick() ½ÇÇàµÊ", "PlayerMove", MB_OK);
}

void PlayerMove::OnTriggerStay(Collider* _collider)
{
    triggered = true;
}

void PlayerMove::OnTriggerExit(Collider* _collider)
{
    triggered = false;
}