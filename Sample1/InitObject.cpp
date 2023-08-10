#include "ComponentHeader.h"
#include "Scripts.h"

void Sample1::InitObject()
{
    // MainCamera
    GameObject* cameraObject = new CameraObject("MainCamera", Vector3(0, 0, 0), Vector3(0, 1, 0));
    CameraMove* cmove = new CameraMove();
    AddComponentToObject(cameraObject, cmove);

    // Bottom
    GameObject* gameObject = new EmptyObject("terrain", Vector3(0, 0, 0));
    Transform* transform = GetComponentFromObject(gameObject, Transform);
    for (int i = -10; i <= 10; ++i)
    {
        for (int j = -10; j <= 10; ++j)
        {
            GameObject* planeObject = new PlaneObject("", Vector3(0, 0, 0), "terraintex.jpg");
            Transform* pTransform = GetComponentFromObject(planeObject, Transform);
            pTransform->SetPosition(Vector3(i * 50, 0, j * 50));
            pTransform->SetScale(Vector3(50, 1, 50));

            transform->AddChild(pTransform);    
        }
    }

    gameObject = new MeshObject("Airplane", Vector3(0, 1, 0), "airplane 2.x");
    transform = GetComponentFromObject(gameObject, Transform);
    BoxCollider* bcollider = new BoxCollider(Vector3(8.0f, 8.0f, 8.0f));
    AddComponentToObject(gameObject, bcollider);
    PlayerMove* pmove = new PlayerMove(0.f);
    AddComponentToObject(gameObject, pmove);

    GameObject* childObject = new EmptyObject("camerapt", Vector3(0, 5, 20));

    Transform* childTransform = GetComponentFromObject(childObject, Transform);
    transform->AddChild(childTransform);
}
