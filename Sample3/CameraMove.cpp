#include "Scripts.h"

void CameraMove::Start()
{
    m_Camera = GetComponentFromObject(gameObject, Camera);
}

void CameraMove::Update()
{
    if (m_Camera == nullptr) return;
   

    if (GetInputBuffer(Key, VK_ESCAPE))
    {
        GameObject::Destroy(Var::RootObject, 1.f);
    }
}