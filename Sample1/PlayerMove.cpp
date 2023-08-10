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

    Vector3 temp = Vector3(0, 0, 0);

    if (GetInputBuffer(KeyHold, 'A')) rotation.y -= (30 * Time::deltaTime);
    if (GetInputBuffer(KeyHold, 'D')) rotation.y += (30 * Time::deltaTime);
    if (GetInputBuffer(KeyHold, 'W')) m_Speed += (10 * Time::deltaTime);
    if (GetInputBuffer(KeyHold, 'S')) m_Speed -= (10 * Time::deltaTime);
    if (GetInputBuffer(KeyHold, 'R')) rotation.x += (30 * Time::deltaTime);
    if (GetInputBuffer(KeyHold, 'F')) rotation.x -= (30 * Time::deltaTime);
    if (GetInputBuffer(KeyHold, 'Q')) rotation.z -= (30 * Time::deltaTime);
    if (GetInputBuffer(KeyHold, 'E')) rotation.z += (30 * Time::deltaTime);

    if (m_Speed < 0.f) m_Speed = 0.f;
    else if (m_Speed > 30.f) m_Speed = 30.f;

    Quaternion transrotation = Functions::EulerToQuaternion(rotation);
    Matrix rotationMatrix;
    D3DXMatrixRotationQuaternion(&rotationMatrix, &transrotation);

    Vector3 frontvec = Vector3(0.0f, 0.0f, -1.0f);
    Vector3 pointOnSphere;
    D3DXVec3TransformCoord(&pointOnSphere, &frontvec, &rotationMatrix);

    m_Direction = pointOnSphere;

    position += pointOnSphere * Time::deltaTime * m_Speed;

    m_Transform->SetPosition(position);
    m_Transform->SetRotation(Functions::EulerToQuaternion(rotation));
}

void PlayerMove::OnTriggerStay(Collider* _collider)
{
    m_isTriggered = true;
}

void PlayerMove::OnTriggerExit(Collider* _collider)
{
    m_isTriggered = false;
}