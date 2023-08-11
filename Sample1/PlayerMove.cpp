#include "Scripts.h"

PlayerMove* PlayerMove::player = nullptr;

PlayerMove::PlayerMove(float p_Speed)
{
    m_Speed = p_Speed;
    m_RotationTorque = Vector3(0, 0, 0);
    m_isLanding = true;
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

    if (m_RotationTorque.y < -0.01f) m_RotationTorque.y += Time::deltaTime;
    else if (m_RotationTorque.y > 0.01f) m_RotationTorque.y -= Time::deltaTime;
    else m_RotationTorque.y = 0;
    if (m_RotationTorque.x < -0.01f) m_RotationTorque.x += Time::deltaTime;
    else if (m_RotationTorque.x > 0.01f) m_RotationTorque.x -= Time::deltaTime;
    else m_RotationTorque.x = 0;
    if (m_RotationTorque.z < -0.01f) m_RotationTorque.z += Time::deltaTime;
    else if (m_RotationTorque.z > 0.01f) m_RotationTorque.z -= Time::deltaTime;
    else m_RotationTorque.z = 0;
    if (m_Speed > 0.01f) m_Speed -= (5 * Time::deltaTime);
    else if (m_Speed < -0.01f) m_Speed += (5 * Time::deltaTime);
    else m_Speed = 0;

    if (GetInputBuffer(KeyHold, 'W')) m_Speed += (20 * Time::deltaTime);
    if (GetInputBuffer(KeyHold, 'S')) m_Speed -= (20 * Time::deltaTime);
    if (m_isLanding)
    {
        if (GetInputBuffer(KeyHold, 'A')) m_RotationTorque.y -= Time::deltaTime * ((abs(m_Speed) * 0.01f) + 1.0f);
        if (GetInputBuffer(KeyHold, 'D')) m_RotationTorque.y += Time::deltaTime * ((abs(m_Speed) * 0.01f) + 1.0f);
        if (GetInputBuffer(KeyHold, 'R')) m_RotationTorque.x += Time::deltaTime * ((m_Speed - 5.f) * 0.05f);
        if (GetInputBuffer(KeyHold, 'F')) m_RotationTorque.x -= Time::deltaTime * ((m_Speed - 5.f) * 0.05f);
    }
    else
    {
        if (GetInputBuffer(KeyHold, 'A')) m_RotationTorque.y -= Time::deltaTime * (m_Speed * 0.01f + 1.0f);
        if (GetInputBuffer(KeyHold, 'D')) m_RotationTorque.y += Time::deltaTime * (m_Speed * 0.01f + 1.0f);
        if (GetInputBuffer(KeyHold, 'R')) m_RotationTorque.x += Time::deltaTime * (m_Speed * 0.025f + 0.5f);
        if (GetInputBuffer(KeyHold, 'F')) m_RotationTorque.x -= Time::deltaTime * (m_Speed * 0.025f + 0.5f);
        if (GetInputBuffer(KeyHold, 'Q')) m_RotationTorque.z -= Time::deltaTime * (m_Speed * 0.025f + 1.f);
        if (GetInputBuffer(KeyHold, 'E')) m_RotationTorque.z += Time::deltaTime * (m_Speed * 0.025f + 1.f);
    }

    if (m_isLanding)
    {
        if (m_RotationTorque.x < 0) m_RotationTorque.x = 0.f;
        if (rotation.x < 0) rotation.x = 0.f;
        m_RotationTorque.z = 0.f;
        rotation.z = 0.f;
    }
    else
    {
        rotation.x -= Time::deltaTime * (10.f - m_Speed * 0.3f);
    }

    if (m_RotationTorque.y < -0.5f) m_RotationTorque.y = -0.5f;
    else if (m_RotationTorque.y > 0.5f) m_RotationTorque.y = 0.5f;
    if (m_RotationTorque.x < -1.f) m_RotationTorque.x = -1.f;
    else if (m_RotationTorque.x > 1.f) m_RotationTorque.x = 1.f;
    if (m_RotationTorque.z < -1.f) m_RotationTorque.z = -1.f;
    else if (m_RotationTorque.z > 1.f) m_RotationTorque.z = 1.f;
    if (m_Speed < 10.f)
    {
        if (m_isLanding)
        {
            if (m_Speed < -5.f) m_Speed = -5.f;
        }
        else
        {
            m_Speed = 10.f;
        }
    }
    else if (m_Speed > 30.f) m_Speed = 30.f;

    rotation.y += m_RotationTorque.y;
    rotation.x += m_RotationTorque.x;
    rotation.z += m_RotationTorque.z;

    if (rotation.x > 60.f) rotation.x = 60.f;
    else if (rotation.x < -60.f) rotation.x = -60.f;

    Quaternion transrotation = Functions::EulerToQuaternion(rotation);
    Matrix rotationMatrix;
    D3DXMatrixRotationQuaternion(&rotationMatrix, &transrotation);

    Vector3 frontvec = Vector3(0.0f, 0.0f, -1.0f);
    Vector3 pointOnSphere;
    D3DXVec3TransformCoord(&pointOnSphere, &frontvec, &rotationMatrix);

    m_Direction = pointOnSphere;

    m_AdditionTorque = 1.f;
    if (rotation.x < 0.f) m_AdditionTorque += rotation.x * -0.02f;
    if (rotation.x > 0.f) m_AdditionTorque += rotation.x * -0.01f;
    position += pointOnSphere * Time::deltaTime * m_Speed * m_AdditionTorque;

    m_Transform->SetPosition(position);
    m_Transform->SetRotation(Functions::EulerToQuaternion(rotation));
}

void PlayerMove::OnTriggerStay(Collider* _collider)
{
    if (!m_isLanding)
    {
        Vector3 rotation = Functions::QuaternionToEuler(m_Transform->GetRotation());

        if (m_Speed > 10.f && (rotation.x < -30.f || abs(rotation.z) > 30.f))
        {
            MessageBox(NULL, "ÆÄ±«µÊ", "DXF Flight", MB_OK);

            m_RotationTorque = Vector3(0, 0, 0);
            m_Speed = 0.f;
        }
    }

    m_isLanding = true;
    m_isTriggered = true;
}

void PlayerMove::OnTriggerExit(Collider* _collider)
{
    m_isLanding = false;
    m_isTriggered = false;
}