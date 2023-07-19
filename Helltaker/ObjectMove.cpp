#include "Scripts.h"

void ObjectMove::Start()
{
    m_Transform = GetComponentFromObject(gameObject, Transform);

    m_MovementVec = Vector3(rand() - (RAND_MAX * 0.5f), 0.f, rand() - (RAND_MAX * 0.5f));
    m_Speed = rand() / RAND_MAX * 10.f + 5.f;
    m_Length = sqrt((fabs(m_MovementVec.x) * fabs(m_MovementVec.x) + fabs(m_MovementVec.z) * fabs(m_MovementVec.z)));
}

void ObjectMove::Update()
{
    if (m_Length == 0.f) return;
    if (m_Transform == nullptr) return;

    m_Transform->m_Position.x += (m_MovementVec.x / m_Length) * Time::deltaTime * m_Speed;
    m_Transform->m_Position.z += (m_MovementVec.z / m_Length) * Time::deltaTime * m_Speed;

    if (m_Transform->m_Position.x > 30) { m_Transform->m_Position.x = 30; m_MovementVec.x *= -1; }
    if (m_Transform->m_Position.x < -30) { m_Transform->m_Position.x = -30; m_MovementVec.x *= -1; }
    if (m_Transform->m_Position.z > 20) { m_Transform->m_Position.z = 20; m_MovementVec.z *= -1; }
    if (m_Transform->m_Position.z < -20) { m_Transform->m_Position.z = -20; m_MovementVec.z *= -1; }
}