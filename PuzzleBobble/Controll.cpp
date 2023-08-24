#include "Scripts.h"

Controll* Controll::m_Controll = nullptr;

void Controll::Awake()
{
    if (m_Controll == nullptr) m_Controll = this;
}

void Controll::Start()
{
    m_RectTransform = GetComponentFromObject(gameObject, RectTransform);
}

void Controll::Update()
{
    if (!m_GameOver)
    {
        if (m_RectTransform == nullptr) return;

        Vector3 rotation = Functions::QuaternionToEuler(m_RectTransform->GetRotation());

        if (GetInputBuffer(KeyHold, 'A') && rotation.z > -70) rotation.z -= (90 * Time::deltaTime);
        if (GetInputBuffer(KeyHold, 'D') && rotation.z < 70) rotation.z += (90 * Time::deltaTime);

        m_RectTransform->SetRotation(Functions::EulerToQuaternion(rotation));
    }
}