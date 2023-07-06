#include "Scripts.h"

void CameraMove::Start()
{
    camera = GetComponentFromObject(gameObject, Camera);
}

void CameraMove::Update()
{
    if (camera == nullptr) return;
    
    if (GetInputBuffer(g_mouse, MouseInput::WHEELUP))
    {
        camera->fovRate *= 1.1;
        if (camera->fovRate > 10.f) camera->fovRate = 10.f;
    }

    if (GetInputBuffer(g_mouse, MouseInput::WHEELDOWN))
    {
        camera->fovRate /= 1.1;
        if (camera->fovRate < 1.f) camera->fovRate = 1.0f;
    }

    if (GetInputBuffer(g_mouse, MouseInput::RBUTTONHOLD))
    {
        PlayerMove* comp = PlayerMove::player;
        if (comp == nullptr) return;

        Transform* transform = GetComponentFromObject(comp->gameObject, Transform);
        if (transform == nullptr) return;

        camera->vLookatPt = Functions::Lerp(camera->vLookatPt, transform->position, Time::deltaTime * LerpT);
    }
    else
    {
        camera->vLookatPt = Functions::Lerp(camera->vLookatPt, Vector3(0, 1, 0), Time::deltaTime * LerpT);
    }

    if (GetInputBuffer(g_key, VK_ESCAPE))
    {
        GameObject::Destroy(g_RootObject);
    }
}