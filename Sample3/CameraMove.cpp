#include "Scripts.h"

CameraMove::CameraMove(Minesweeper* Sweeper) {
    Mine_Sweeper = Sweeper;
}

void CameraMove::Start()
{
    m_Camera = GetComponentFromObject(gameObject, Camera);
}

void CameraMove::Update()
{
    if (m_Camera == nullptr) return;
   
    Transform* Trans = GetComponentFromObject(gameObject, Transform);
    int Size = Mine_Sweeper->GetMapSize();
    Trans->SetPosition(Vector3(0, 2 * Size, -Size));

    if (GetInputBuffer(Key, VK_ESCAPE))
    {
        GameObject::Destroy(Var::RootObject, 1.f);
    }
}