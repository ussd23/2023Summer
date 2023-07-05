#include "ComponentHeader.h"
#include "Scripts.h"

void ObjectMove::Start()
{
    transform = GetComponentFromObject(gameObject, Transform);

    movementvec = D3DXVECTOR3(rand() - (RAND_MAX / 2), 0.f, rand() - (RAND_MAX / 2));
    movespeed = rand() / RAND_MAX * 10.f + 5.f;
    length = sqrt((fabs(movementvec.x) * fabs(movementvec.x) + fabs(movementvec.z) * fabs(movementvec.z)));
}

void ObjectMove::Update()
{
    if (length == 0.f) return;
    if (transform == nullptr) return;

    transform->position.x += (movementvec.x / length) * Time::deltaTime * movespeed;
    transform->position.z += (movementvec.z / length) * Time::deltaTime * movespeed;

    if (transform->position.x > 30) { transform->position.x = 30; movementvec.x *= -1; }
    if (transform->position.x < -30) { transform->position.x = -30; movementvec.x *= -1; }
    if (transform->position.z > 20) { transform->position.z = 20; movementvec.z *= -1; }
    if (transform->position.z < -20) { transform->position.z = -20; movementvec.z *= -1; }
}