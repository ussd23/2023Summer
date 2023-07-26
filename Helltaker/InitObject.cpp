#include "ComponentHeader.h"
#include "Scripts.h"

void Helltaker::InitObject()
{
    // Text (RectTransform)
    GameObject* gameObject = new GameObject("Text");
    RectTransform* rect = new RectTransform(Vector2(300, 55), Vector3(0.f, 0.f, 0.f), Vector2(1.f, 1.f), Vector2(600, 110));
    AddComponentToObject(gameObject, rect);
    TextRenderer* text = new TextRenderer("맑은 고딕", 16, "");
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
    vec.push_back({ 30.0f, 0.0f, -20.0f, 0x538378ff, 1.0f, 1.0f });
    vec.push_back({ 30.0f, 0.0f,  20.0f, 0x538378ff, 1.0f, 0.0f });
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

    // Tiger (Object) -현재 sun의 child로 등록된 상태
    GameObject* ChildObject = new GameObject("Tiger");
    transform = new Transform(Vector3(-10.f, 1.f, -10.f), Vector3(0.f, 0.f, 0.f), Vector3(2.f, 2.f, 2.f));
    AddComponentToObject(ChildObject, transform);
    mesh = new MeshRenderer("tiger.x");
    AddComponentToObject(ChildObject, mesh);
    BoxCollider* bcollider = new BoxCollider(Vector3(3.0f, 3.0f, 3.0f));
    AddComponentToObject(ChildObject, bcollider);
    ObjectMove* omove = new ObjectMove();
    AddComponentToObject(ChildObject, omove);
    Transform* Ptransform = GetComponentFromObject(gameObject, Transform);  //부모 오브젝트의 트랜스폼 받아옴
    AddObjectToScene(ChildObject, Ptransform, transform);   //루트 트랜스폼 대신 부모의 트랜스폼을 넣음

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

    // Neptune (Object)
    gameObject = new GameObject("Neptune");
    transform = new Transform(Vector3(5.f, 2.5f, 5.f), Vector3(0.f, 0.f, 0.f), Vector3(2.f, 2.f, 2.f));
    AddComponentToObject(gameObject, transform);
    mesh = new MeshRenderer("neptune.x");
    AddComponentToObject(gameObject, mesh);
    scollider = new SphereCollider(1.2f);
    AddComponentToObject(gameObject, scollider);
    omove = new ObjectMove();
    AddComponentToObject(gameObject, omove);
    AddObjectToScene(gameObject, g_RootTransform, transform);

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

    gameObject = new GameObject("btn");

    //Button* btn = new Button(Vector2(300, SCREENSIZEY - 50), Vector3(0.f, 0.f, 0.f), Vector2(1.f, 1.f), Vector2(200, 100), "earthmap1k.jpg", 0xffffffff, Vector2(4, 4), Vector2(0, 0));
    //AddComponentToObject(gameObject, btn);
    //btn->InitBtn();

    rect = new RectTransform(Vector2(300, SCREENSIZEY - 50), Vector3(0.f, 0.f, 0.f), Vector2(1.f, 1.f), Vector2(200, 100));
    AddComponentToObject(gameObject, rect);
    spr = new SpriteRenderer("earthmap1k.jpg", Vector2(4, 4), Vector2(0, 0));
    AddComponentToObject(gameObject, spr);
    mouse = new MouseFunction();
    AddComponentToObject(gameObject, mouse);

    ButtonTest* test = new ButtonTest();
    AddComponentToObject(gameObject, test);
    AddObjectToScene(gameObject, g_RootRectTransform, rect);

}
