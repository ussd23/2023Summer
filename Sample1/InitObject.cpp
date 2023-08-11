#include "ComponentHeader.h"
#include "Scripts.h"

void Sample1::InitObject()
{
    // Text (RectTransform)
    GameObject* gameObject = new TextObject("Text", Vector2(600, 110), Vector2(300, 55), "맑은 고딕", 16, "");
    TopText* ttext = new TopText();
    AddComponentToObject(gameObject, ttext);

    // MainCamera
    GameObject* cameraObject = new CameraObject("MainCamera", Vector3(0, 0, 0), Vector3(0, 1, 0));
    CameraMove* cmove = new CameraMove();
    AddComponentToObject(cameraObject, cmove);

    // Bottom
    gameObject = new PlaneObject("", Vector3(0, 0, 0), "terraintex.jpg");
    Transform* transform = GetComponentFromObject(gameObject, Transform);
    transform->SetScale(Vector3(1000, 1, 1000));
    VerticeRenderer* vertice = GetComponentFromObject(gameObject, VerticeRenderer);
    vertice->m_Vertices[0].tv = 20.f;
    vertice->m_Vertices[2].tu = 20.f;
    vertice->m_Vertices[2].tv = 20.f;
    vertice->m_Vertices[3].tu = 20.f;
    BoxCollider* bcollider = new BoxCollider(Vector3(1, 1, 1), false);
    AddComponentToObject(gameObject, bcollider);

    gameObject = new MeshObject("Airplane", Vector3(0, 1, 0), "airplane 2.x");
    transform = GetComponentFromObject(gameObject, Transform);
    bcollider = new BoxCollider(Vector3(8.0f, 4.0f, 8.0f));
    AddComponentToObject(gameObject, bcollider);
    PlayerMove* pmove = new PlayerMove(0.f);
    AddComponentToObject(gameObject, pmove);

    GameObject* childObject = new EmptyObject("camerapt", Vector3(0, 5, 20));

    Transform* childTransform = GetComponentFromObject(childObject, Transform);
    transform->AddChild(childTransform);
}
