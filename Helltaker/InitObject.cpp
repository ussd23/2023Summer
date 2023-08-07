#include "ComponentHeader.h"
#include "Scripts.h"

void Helltaker::InitObject()
{
    SceneManager::LoadScene("scene1");

    return;

    // Text (RectTransform)
    GameObject* gameObject = new TextObject("Text", Vector2(600, 110), Vector2(300, 55), "맑은 고딕", 16, "");
    TopText* ttext = new TopText();
    AddComponentToObject(gameObject, ttext);
    MouseFunction* mouse = new MouseFunction(true);
    AddComponentToObject(gameObject, mouse);

    // MainCamera
    gameObject = new CameraObject("MainCamera", Vector3(0, 40, -40), Vector3(0, 1, 0));
    CameraMove* cmove = new CameraMove();
    AddComponentToObject(gameObject, cmove);

    // Bottom
    gameObject = new PlaneObject("Bottom", Vector3(0, 0, 0), "earthmap1k.jpg");
    vector<Vertex> vec;
    vec.push_back({ -30.0f, 0.0f, -20.0f, 0x5383d8ff, 0.0f, 1.0f });
    vec.push_back({ -30.0f, 0.0f,  20.0f, 0x5383d8ff, 0.0f, 0.0f });
    vec.push_back({  30.0f, 0.0f, -20.0f, 0x538378ff, 1.0f, 1.0f });
    vec.push_back({  30.0f, 0.0f,  20.0f, 0x538378ff, 1.0f, 0.0f });
    VerticeRenderer* vertice = GetComponentFromObject(gameObject, VerticeRenderer);
    vertice->m_RectSize = Vector2(3, 3);
    vertice->m_RectIndex = Vector2(2, 0);
    vertice->m_Vertices = vec;
    Animator* animator = new Animator(0, MAXINT, 1.f, true);
    AddComponentToObject(gameObject, animator);

    // Sun (Player)
    gameObject = new MeshObject("Sun", Vector3(0, 1, 0), "sun.x");
    PlayerMove* pmove = new PlayerMove(20.f);
    AddComponentToObject(gameObject, pmove);
    SphereCollider* scollider = new SphereCollider(1.0f);
    AddComponentToObject(gameObject, scollider);
    mouse = new MouseFunction();
    AddComponentToObject(gameObject, mouse);

    // Child
    GameObject* childObject = new MeshObject("Sun", Vector3(0, 0, 5), "sun.x");
    Transform* transform = GetComponentFromObject(childObject, Transform);
    transform->SetScale(Vector3(0.5f, 0.5f, 0.5f));
    Transform* parentTransform = GetComponentFromObject(gameObject, Transform);
    transform->SetParent(parentTransform);

    // Tiger (Object)
    gameObject = new MeshObject("Tiger", Vector3(-10, 1, -10), "tiger.x");
    transform = GetComponentFromObject(gameObject, Transform);
    transform->SetScale(Vector3(2, 2, 2));
    BoxCollider* bcollider = new BoxCollider(Vector3(3.0f, 3.0f, 3.0f));
    AddComponentToObject(gameObject, bcollider);
    ObjectMove* omove = new ObjectMove();
    AddComponentToObject(gameObject, omove);

    // Airplane (Object)
    gameObject = new MeshObject("Airplane", Vector3(-10, 1, 5), "airplane 2.x");
    transform = GetComponentFromObject(gameObject, Transform);
    transform->SetScale(Vector3(0.6f, 0.6f, 0.6f));
    bcollider = new BoxCollider(Vector3(8.0f, 8.0f, 8.0f));
    AddComponentToObject(gameObject, bcollider);
    omove = new ObjectMove();
    AddComponentToObject(gameObject, omove);

    // Earth (Object)
    gameObject = new MeshObject("Earth", Vector3(5, 2.5f, -10), "earth.x");
    transform = GetComponentFromObject(gameObject, Transform);
    transform->SetScale(Vector3(2, 2, 2));
    scollider = new SphereCollider(1.2f);
    AddComponentToObject(gameObject, scollider);
    omove = new ObjectMove();
    AddComponentToObject(gameObject, omove);

    // Neptune (Object)
    gameObject = new MeshObject("Neptune", Vector3(5, 2.5f, 5), "neptune.x");
    transform = GetComponentFromObject(gameObject, Transform);
    transform->SetScale(Vector3(2, 2, 2));
    scollider = new SphereCollider(1.2f, true);
    AddComponentToObject(gameObject, scollider);
    omove = new ObjectMove();
    AddComponentToObject(gameObject, omove);

    // Instantiate Test
    for (int i = 0; i < 100; ++i)
    {
        GameObject::Instantiate(gameObject);
    }

    // Sprite (RectTransform)
    gameObject = new SpriteObject("Sprite", Vector2(200, 100), Vector2(100, SCREENSIZEY - 50), "earthmap1k.jpg");
    SpriteRenderer* sprite = GetComponentFromObject(gameObject, SpriteRenderer);
    sprite->m_RectIndex = Vector2(0, 0);
    sprite->m_RectSize = Vector2(4, 4);
    vector<AnimationInfo> avec;
    avec.push_back({ Vector2(0,0), 1.0f });
    avec.push_back({ Vector2(1,1), 0.5f });
    avec.push_back({ Vector2(2,2), 0.2f });
    avec.push_back({ Vector2(3,3), 0.2f });
    animator = new Animator(avec);
    AddComponentToObject(gameObject, animator);

    SceneManager::SaveScene("scene1");
}
