#include "Scripts.h"

void CameraMove::Start()
{
    m_Camera = GetComponentFromObject(gameObject, Camera);
}

void CameraMove::Update()
{
    if (m_Camera == nullptr) return;
    
    if (GetInputBuffer(Mouse, MouseInput::WHEELUP))
    {
        m_Camera->m_FovRate *= 1.1;
        if (m_Camera->m_FovRate > 10.f) m_Camera->m_FovRate = 10.f;
    }

    if (GetInputBuffer(Mouse, MouseInput::WHEELDOWN))
    {
        m_Camera->m_FovRate /= 1.1;
        if (m_Camera->m_FovRate < 1.f) m_Camera->m_FovRate = 1.0f;
    }

    if (GetInputBuffer(Mouse, MouseInput::RBUTTONHOLD))
    {
        PlayerMove* comp = PlayerMove::player;
        if (comp == nullptr) return;

        Transform* transform = GetComponentFromObject(comp->gameObject, Transform);
        if (transform == nullptr) return;

        m_Camera->m_LookatPt = Functions::Lerp(m_Camera->m_LookatPt, transform->GetWorldPosition(), Time::deltaTime * m_LerpT);
    }
    else
    {
        m_Camera->m_LookatPt = Functions::Lerp(m_Camera->m_LookatPt, Vector3(0, 1, 0), Time::deltaTime * m_LerpT);
    }

    if (GetInputBuffer(Key, VK_ESCAPE))
    {
        GameObject::Destroy(Var::RootObject, 1.f);
    }
}