#include "Scripts.h"

void ObjectMove::Start()
{
    m_Transform = GetComponentFromObject(gameObject, Transform);

    if (m_Transform == nullptr) return;

    Vector3 rotation = Functions::QuaternionToEuler(m_Transform->GetRotation());
    rotation.x = (rand() / (float)RAND_MAX) * 10;
    rotation.z = (rand() / (float)RAND_MAX) * 10;
    m_Transform->SetRotation(Functions::EulerToQuaternion(rotation));

    m_Speed = (rand() / (float)RAND_MAX) * 200 - 100;
}

void ObjectMove::Update()
{
    if (m_Transform == nullptr) return;

    Vector3 rotation = Functions::QuaternionToEuler(m_Transform->GetRotation());
    rotation.y += m_Speed * Time::deltaTime;
    m_Transform->SetRotation(Functions::EulerToQuaternion(rotation));
}