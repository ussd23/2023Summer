#include "Scripts.h"

Controll* Controll::controll = nullptr;

void Controll::Awake()
{
    if (controll == nullptr) controll = this;
}

void Controll::Start()
{
    m_RectTransform = GetComponentFromObject(gameObject, RectTransform);
}

void Controll::Update()
{
    if (m_RectTransform == nullptr) return;

    Vector3 rotation = Functions::QuaternionToEuler(m_RectTransform->GetRotation());

    if (GetInputBuffer(KeyHold, 'A')) rotation.z -= (90 * Time::deltaTime);
    if (GetInputBuffer(KeyHold, 'D')) rotation.z += (90 * Time::deltaTime);

    m_RectTransform->SetRotation(Functions::EulerToQuaternion(rotation));
}