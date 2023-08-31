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
    gameObject = new PlaneObject("ter", Vector3(0, 0, 0), "terraintex.jpg");
    Transform* transform = GetComponentFromObject(gameObject, Transform);
    transform->SetScale(Vector3(10000, 1, 10000));
    VerticeRenderer* vertice = GetComponentFromObject(gameObject, VerticeRenderer);

    vector<Vertex> vec = vertice->GetVertices();
    vec[0].tv = 100.f;
    vec[2].tu = 100.f;
    vec[2].tv = 100.f;
    vec[3].tu = 100.f;
    vertice->ChangeVertices(vec);
    BoxCollider* bcollider = new BoxCollider(Vector3(1, 1, 1), false);
    AddComponentToObject(gameObject, bcollider);

    vector<string> models;
    models.push_back("sun.x");
    models.push_back("mercury.x");
    models.push_back("venus.x");
    models.push_back("earth.x");
    models.push_back("mars.x");
    models.push_back("jupiter.x");
    models.push_back("saturn.x");
    models.push_back("uranus.x");
    models.push_back("neptune.x");

    // Neptune (Object)
    for (int i = 0; i < 500; ++i)
    {
        Vector3 pos = Vector3((rand() - RAND_MAX / 2) * 0.25f, (rand() / (float)RAND_MAX) * 80 + 20, (rand() - RAND_MAX / 2) * 0.25f);
        float scale = (rand() / (float)RAND_MAX) * 20 + 5;

        gameObject = new MeshObject("CollisionObject", pos, models[rand() % 9]);
        transform = GetComponentFromObject(gameObject, Transform);
        transform->SetScale(Vector3(scale, scale, scale));
        SphereCollider* scollider = new SphereCollider(1.0f, true);
        AddComponentToObject(gameObject, scollider);
        ObjectMove* omove = new ObjectMove();
        AddComponentToObject(gameObject, omove);
    }

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
