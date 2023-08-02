#include "ComponentHeader.h"
#include "Scripts.h"

void Helltaker::InitObject()
{
    // Text (RectTransform)
    GameObject* gameObject = new GameObject("Text");
    RectTransform* rect = new RectTransform(Vector2(300, 55), Vector3(0.f, 0.f, 0.f), Vector2(1.f, 1.f), Vector2(600, 110));
    AddComponentToObject(gameObject, rect);
    TextRenderer* text = new TextRenderer("¸¼Àº °íµñ", 16, "");
    AddComponentToObject(gameObject, text);
    TopText* ttext = new TopText();
    AddComponentToObject(gameObject, ttext);
    MouseFunction* mouse = new MouseFunction();
    AddComponentToObject(gameObject, mouse);
    AddObjectToScene(gameObject, g_RootRectTransform, rect);

    // MainCamera
    gameObject = new GameObject("MainCamera");
    Transform* transform = new Transform(Vector3(0, 40, -40), Vector3(0.f, 0.f, 0.f), Vector3(1.f, 1.f, 1.f));
    AddComponentToObject(gameObject, transform);
    Camera* camera = new Camera(Vector3(0, 1, 0));
    AddComponentToObject(gameObject, camera);
    CameraMove* cmove = new CameraMove();
    AddComponentToObject(gameObject, cmove);
    AddObjectToScene(gameObject, g_RootTransform, transform);

    // Bottom
    gameObject = new GameObject("Bottom");
    transform = new Transform(Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 0.f), Vector3(1.f, 1.f, 1.f));
    AddComponentToObject(gameObject, transform);
    vector<Vertex> vec;
    vec.push_back({ -30.0f, 0.0f, -20.0f, 0x5383d8ff, 0.0f, 1.0f });
    vec.push_back({ -30.0f, 0.0f,  20.0f, 0x5383d8ff, 0.0f, 0.0f });
    vec.push_back({  30.0f, 0.0f, -20.0f, 0x538378ff, 1.0f, 1.0f });
    vec.push_back({  30.0f, 0.0f,  20.0f, 0x538378ff, 1.0f, 0.0f });
    VerticeRenderer* vertice = new VerticeRenderer("earthmap1k.jpg", Vector2(3, 3), Vector2(2, 0), vec, D3DPRIMITIVETYPE::D3DPT_TRIANGLESTRIP, 0, 2);
    AddComponentToObject(gameObject, vertice);
    Animator* animator = new Animator(0, MAXINT, 1.f, true);
    AddComponentToObject(gameObject, animator);
    AddObjectToScene(gameObject, g_RootTransform, transform);

    // Sun (Player)
    gameObject = new GameObject("Sun");
    transform = new Transform(Vector3(0.f, 1.f, 0.f), Vector3(0.f, 0.f, 0.f), Vector3(1.f, 1.f, 1.f));
    AddComponentToObject(gameObject, transform);
    MeshRenderer* mesh = new MeshRenderer("sun.x");
    AddComponentToObject(gameObject, mesh);
    PlayerMove* pmove = new PlayerMove(20.f);
    AddComponentToObject(gameObject, pmove);
    SphereCollider* scollider = new SphereCollider(1.0f);
    AddComponentToObject(gameObject, scollider);
    mouse = new MouseFunction();
    AddComponentToObject(gameObject, mouse);
    AddObjectToScene(gameObject, g_RootTransform, transform);

    // Child
    GameObject* childObject = new GameObject("Child");
    Transform* childTransform = new Transform(Vector3(0.f, 0.f, 5.f), Vector3(0.f, 0.f, 0.f), Vector3(0.5f, 0.5f, 0.5f));
    AddComponentToObject(childObject, childTransform);
    mesh = new MeshRenderer("sun.x");
    AddComponentToObject(childObject, mesh);
    AddObjectToScene(childObject, transform, childTransform);

    // Tiger (Object)
    gameObject = new GameObject("Tiger");
    transform = new Transform(Vector3(-10.f, 1.f, -10.f), Vector3(0.f, 0.f, 0.f), Vector3(2.f, 2.f, 2.f));
    AddComponentToObject(gameObject, transform);
    mesh = new MeshRenderer("tiger.x");
    AddComponentToObject(gameObject, mesh);
    BoxCollider* bcollider = new BoxCollider(Vector3(3.0f, 3.0f, 3.0f));
    AddComponentToObject(gameObject, bcollider);
    ObjectMove* omove = new ObjectMove();
    AddComponentToObject(gameObject, omove);
    AddObjectToScene(gameObject, g_RootTransform, transform);

    // Airplane (Object)
    gameObject = new GameObject("Airplane");
    transform = new Transform(Vector3(-10.f, 1.f, 5.f), Vector3(0.f, 0.f, 0.f), Vector3(0.6f, 0.6f, 0.6f));
    AddComponentToObject(gameObject, transform);
    mesh = new MeshRenderer("airplane 2.x");
    AddComponentToObject(gameObject, mesh);
    bcollider = new BoxCollider(Vector3(8.0f, 8.0f, 8.0f));
    AddComponentToObject(gameObject, bcollider);
    omove = new ObjectMove();
    AddComponentToObject(gameObject, omove);
    AddObjectToScene(gameObject, g_RootTransform, transform);

    // Earth (Object)
    gameObject = new GameObject("Earth");
    transform = new Transform(Vector3(5.f, 2.5f, -10.f), Vector3(0.f, 0.f, 0.f), Vector3(2.f, 2.f, 2.f));
    AddComponentToObject(gameObject, transform);
    mesh = new MeshRenderer("earth.x");
    AddComponentToObject(gameObject, mesh);
    scollider = new SphereCollider(1.2f);
    AddComponentToObject(gameObject, scollider);
    omove = new ObjectMove();
    AddComponentToObject(gameObject, omove);
    AddObjectToScene(gameObject, g_RootTransform, transform);

    // Serialize Test
    Json::Value jTransform;
    Json::Value jMesh;
    Json::Value jScollider;
    Json::Value jOmove;
    transform->JsonSerialize(jTransform);
    mesh->JsonSerialize(jMesh);
    scollider->JsonSerialize(jScollider);
    omove->JsonSerialize(jOmove);

    // Deserialize Test
    gameObject = new GameObject("Deserialize Test");
    transform = new Transform();
    mesh = new MeshRenderer();
    scollider = new SphereCollider();
    omove = new ObjectMove();
    transform->JsonDeserialize(jTransform);
    mesh->JsonDeserialize(jMesh);
    scollider->JsonDeserialize(jScollider);
    omove->JsonDeserialize(jOmove);
    AddComponentToObject(gameObject, transform);
    AddComponentToObject(gameObject, mesh);
    AddComponentToObject(gameObject, scollider);
    AddComponentToObject(gameObject, omove);
    AddObjectToScene(gameObject, g_RootTransform, transform);

    // Neptune (Object)
    for (int i = 0; i < 300; ++i)
    {
        gameObject = new GameObject("Neptune");
        transform = new Transform(Vector3(5.f, 2.5f, 5.f), Vector3(0.f, 0.f, 0.f), Vector3(2.f, 2.f, 2.f));
        AddComponentToObject(gameObject, transform);
        mesh = new MeshRenderer("neptune.x");
        AddComponentToObject(gameObject, mesh);
        scollider = new SphereCollider(1.2f, true);
        AddComponentToObject(gameObject, scollider);
        omove = new ObjectMove();
        AddComponentToObject(gameObject, omove);
        AddObjectToScene(gameObject, g_RootTransform, transform);
    }

    // Sprite (RectTransform)
    gameObject = new GameObject("Sprite");
    rect = new RectTransform(Vector2(100, SCREENSIZEY - 50), Vector3(0.f, 0.f, 0.f), Vector2(1.f, 1.f), Vector2(200, 100));
    AddComponentToObject(gameObject, rect);
    SpriteRenderer* spr = new SpriteRenderer("earthmap1k.jpg", Vector2(4, 4), Vector2(0, 0));
    AddComponentToObject(gameObject, spr);
    vector<AnimationInfo> avec;
    avec.push_back({ Vector2(0,0), 1.0f });
    avec.push_back({ Vector2(1,1), 0.5f });
    avec.push_back({ Vector2(2,2), 0.2f });
    avec.push_back({ Vector2(3,3), 0.2f });
    animator = new Animator(avec);
    AddComponentToObject(gameObject, animator);
    AddObjectToScene(gameObject, g_RootRectTransform, rect);
}
