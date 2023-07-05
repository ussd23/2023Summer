#include "ComponentHeader.h"
#include "Scripts.h"

void Game::InitObject()
{
    // Text (RectTransform)
    GameObject* gameObject = new GameObject("Text");
    RectTransform* rect = new RectTransform(gameObject, D3DXVECTOR2(300, 55), D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR2(1.f, 1.f), D3DXVECTOR2(600, 110));
    AddComponentToObject(gameObject, rect);
    TextRenderer* text = new TextRenderer(gameObject, "¸¼Àº °íµñ", 16, "");
    AddComponentToObject(gameObject, text);
    TopText* ttext = new TopText();
    AddComponentToObject(gameObject, ttext);
    MouseFunction* mouse = new MouseFunction();
    AddComponentToObject(gameObject, mouse);
    AddObjectToScene(gameObject, g_RootRectTransform, rect);

    // MainCamera
    gameObject = new GameObject("MainCamera");
    Transform* transform = new Transform(gameObject, D3DXVECTOR3(0, 40, -40), D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR3(1.f, 1.f, 1.f));
    AddComponentToObject(gameObject, transform);
    Camera* camera = new Camera(gameObject, D3DXVECTOR3(0, 1, 0));
    AddComponentToObject(gameObject, camera);
    CameraMove* cmove = new CameraMove();
    AddComponentToObject(gameObject, cmove);
    AddObjectToScene(gameObject, g_RootTransform, transform);

    // Bottom
    gameObject = new GameObject("Bottom");
    transform = new Transform(gameObject, D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR3(1.f, 1.f, 1.f));
    AddComponentToObject(gameObject, transform);
    vector<CUSTOMVERTEX> vec;
    vec.push_back({ -30.0f, 0.0f, -20.0f, 0x5383d8ff, 0.0f, 1.0f });
    vec.push_back({ -30.0f, 0.0f,  20.0f, 0x5383d8ff, 0.0f, 0.0f });
    vec.push_back({  30.0f, 0.0f, -20.0f, 0x538378ff, 1.0f, 1.0f });
    vec.push_back({  30.0f, 0.0f,  20.0f, 0x538378ff, 1.0f, 0.0f });
    VerticeRenderer* vertice = new VerticeRenderer(gameObject, "earthmap1k.jpg", D3DXVECTOR2(3, 3), D3DXVECTOR2(2, 0), vec, D3DPRIMITIVETYPE::D3DPT_TRIANGLESTRIP, 0, 2);
    AddComponentToObject(gameObject, vertice);
    Animator* animator = new Animator(0, MAXINT, 1.f, true);
    AddComponentToObject(gameObject, animator);
    AddObjectToScene(gameObject, g_RootTransform, transform);

    // Sun (Player)
    gameObject = new GameObject("Sun");
    transform = new Transform(gameObject, D3DXVECTOR3(0.f, 1.f, 0.f), D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR3(1.f, 1.f, 1.f));
    AddComponentToObject(gameObject, transform);
    MeshRenderer* mesh = new MeshRenderer(gameObject, "sun.x");
    AddComponentToObject(gameObject, mesh);
    PlayerMove* pmove = new PlayerMove(20.f);
    AddComponentToObject(gameObject, pmove);
    SphereCollider* scollider = new SphereCollider(1.0f);
    AddComponentToObject(gameObject, scollider);
    mouse = new MouseFunction();
    AddComponentToObject(gameObject, mouse);
    AddObjectToScene(gameObject, g_RootTransform, transform);

    // Tiger (Object)
    gameObject = new GameObject("Tiger");
    transform = new Transform(gameObject, D3DXVECTOR3(-10.f, 1.f, -10.f), D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR3(2.f, 2.f, 2.f));
    AddComponentToObject(gameObject, transform);
    mesh = new MeshRenderer(gameObject, "tiger.x");
    AddComponentToObject(gameObject, mesh);
    BoxCollider* bcollider = new BoxCollider(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
    AddComponentToObject(gameObject, bcollider);
    ObjectMove* omove = new ObjectMove();
    AddComponentToObject(gameObject, omove);
    AddObjectToScene(gameObject, g_RootTransform, transform);

    // Airplane (Object)
    gameObject = new GameObject("Airplane");
    transform = new Transform(gameObject, D3DXVECTOR3(-10.f, 1.f, 5.f), D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR3(0.6f, 0.6f, 0.6f));
    AddComponentToObject(gameObject, transform);
    mesh = new MeshRenderer(gameObject, "airplane 2.x");
    AddComponentToObject(gameObject, mesh);
    bcollider = new BoxCollider(D3DXVECTOR3(8.0f, 8.0f, 8.0f));
    AddComponentToObject(gameObject, bcollider);
    omove = new ObjectMove();
    AddComponentToObject(gameObject, omove);
    AddObjectToScene(gameObject, g_RootTransform, transform);

    // Earth (Object)
    gameObject = new GameObject("Earth");
    transform = new Transform(gameObject, D3DXVECTOR3(5.f, 2.5f, -10.f), D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR3(2.f, 2.f, 2.f));
    AddComponentToObject(gameObject, transform);
    mesh = new MeshRenderer(gameObject, "earth.x");
    AddComponentToObject(gameObject, mesh);
    scollider = new SphereCollider(1.2f);
    AddComponentToObject(gameObject, scollider);
    omove = new ObjectMove();
    AddComponentToObject(gameObject, omove);
    AddObjectToScene(gameObject, g_RootTransform, transform);

    // Neptune (Object)
    gameObject = new GameObject("Neptune");
    transform = new Transform(gameObject, D3DXVECTOR3(5.f, 2.5f, 5.f), D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR3(2.f, 2.f, 2.f));
    AddComponentToObject(gameObject, transform);
    mesh = new MeshRenderer(gameObject, "neptune.x");
    AddComponentToObject(gameObject, mesh);
    scollider = new SphereCollider(1.2f);
    AddComponentToObject(gameObject, scollider);
    omove = new ObjectMove();
    AddComponentToObject(gameObject, omove);
    AddObjectToScene(gameObject, g_RootTransform, transform);

    // Sprite (RectTransform)
    gameObject = new GameObject("Sprite");
    rect = new RectTransform(gameObject, D3DXVECTOR2(100, SCREENSIZEY - 50), D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR2(1.f, 1.f), D3DXVECTOR2(200, 100));
    AddComponentToObject(gameObject, rect);
    SpriteRenderer* spr = new SpriteRenderer(gameObject, "earthmap1k.jpg", D3DXVECTOR2(4,4), D3DXVECTOR2(0,0));
    AddComponentToObject(gameObject, spr);
    animator = new Animator(0.5f);
    AddComponentToObject(gameObject, animator);
    AddObjectToScene(gameObject, g_RootRectTransform, rect);

    //gameObject->GetComponent<SpriteRenderer>();

    //gameObject = nullptr;
    //GameObject::Destroy(gameObject);
    //gameObject = nullptr;

    //delete gameObject;
}
