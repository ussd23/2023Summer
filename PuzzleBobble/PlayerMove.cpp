#include "Scripts.h"

PlayerMove* PlayerMove::player = nullptr;

PlayerMove::PlayerMove(float p_Speed)
{
    m_Speed = p_Speed;
}

void PlayerMove::Awake()
{
    if (player == nullptr) player = this;
}

void PlayerMove::Start()
{
    m_Transform = GetComponentFromObject(gameObject, Transform);
}

void PlayerMove::Update()
{
    if (m_Transform == nullptr) return;

    Vector3 position = m_Transform->GetPosition();
    Vector3 rotation = Functions::QuaternionToEuler(m_Transform->GetRotation());
    Vector3 scale = m_Transform->GetScale();

    Vector3 temp = Vector3(0, 0, 0);
    float length;

    if (GetInputBuffer(KeyHold, 'A')) temp.x -= 0.1f;
    if (GetInputBuffer(KeyHold, 'D')) temp.x += 0.1f;
    if (GetInputBuffer(KeyHold, 'W')) temp.y += 0.1f;
    if (GetInputBuffer(KeyHold, 'S')) temp.y -= 0.1f;

    if (GetInputBuffer(KeyHold, 'Q')) rotation.y -= (90 * Time::deltaTime);
    if (GetInputBuffer(KeyHold, 'E')) rotation.y += (90 * Time::deltaTime);

    if (GetInputBuffer(KeyHold, 'R')) scale *= 1.01f;
    if (GetInputBuffer(KeyHold, 'F')) scale /= 1.01f;

    length = sqrt((fabs(temp.x) * fabs(temp.x) + fabs(temp.y) * fabs(temp.y)));
    if (length > 0.f)
    {
        position.x += (temp.x / length) * Time::deltaTime * m_Speed;
        position.y += (temp.y / length) * Time::deltaTime * m_Speed;

        if (position.x > 30) position.x = 30;
        if (position.x < -30) position.x = -30;
        if (position.y > 20) position.y = 20;
        if (position.y < -20) position.y = -20;
    }

    m_Transform->SetPosition(position);
    m_Transform->SetRotation(Functions::EulerToQuaternion(rotation));
    m_Transform->SetScale(scale);
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