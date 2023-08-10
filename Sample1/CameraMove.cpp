#include "Scripts.h"

void CameraMove::Start()
{
    m_Camera = GetComponentFromObject(gameObject, Camera);
}

void CameraMove::Update()
{
    if (m_Camera == nullptr) return;

    PlayerMove* comp = PlayerMove::player;
    if (comp == nullptr) return;

    Transform* transform = GetComponentFromObject(comp->gameObject, Transform);
    if (transform == nullptr) return;

    m_Camera->m_LookatPt = Functions::Lerp(m_Camera->m_LookatPt, transform->GetWorldPosition(), Time::deltaTime * m_LerpT);

    Transform* camerapt = GetComponentFromObject(gameObject, Transform);
    Vector3 camerapos = camerapt->GetPosition();

    camerapt->SetPosition(Functions::Lerp(camerapos, transform->GetChild(0)->GetWorldPosition(), Time::deltaTime * m_LerpT));
}