#include "ComponentHeader.h"

Camera* Camera::main = nullptr;

Camera::Camera(const Vector3& p_Lookat)
{
    m_LookatPt = p_Lookat;
    m_UpVec = Vector3(0.0f, 1.1f, 0.0f);
    if (main == nullptr) main = this;
}

void Camera::Start()
{
    m_Transform = GetComponentFromObject(gameObject, Transform);
}

void Camera::Update()
{
    m_EyePt = m_Transform->GetWorldPosition();
}