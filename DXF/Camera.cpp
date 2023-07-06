#include "ComponentHeader.h"

Camera* Camera::main = nullptr;

Camera::Camera(GameObject* _gameObject, Vector3 _Lookat)
{
    gameObject = _gameObject;
    vLookatPt = _Lookat;
    vUpVec = Vector3(0.0f, 1.1f, 0.0f);
    if (main == nullptr) main = this;
}

void Camera::Start()
{
    transform = GetComponentFromObject(gameObject, Transform);
}

void Camera::Update()
{
    vEyePt = transform->GetWorldPosition();
}