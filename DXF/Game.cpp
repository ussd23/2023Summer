#include "DXHeader.h"
#include "Global.h"
#include "Functions.h"
#include "GameObject.h"
#include "ComponentHeader.h"

namespace Time
{;
UINT pastTime = 0;
int sec = 0;
int frames = 0;
int passedFrames = 0;
int passedTime = 0;
}

void Game::TimeUpdate()
{
    ++Time::frames;
    ++Time::passedFrames;

    UINT iTime = GetTickCount64();

    if (Time::pastTime == 0) Time::pastTime = iTime;
    if (Time::sec == 0) Time::sec = iTime / 1000;

    Time::deltaTime = (iTime - Time::pastTime) / 1000.0f;

    if (Time::sec != iTime / 1000)
    {
        Time::sec = iTime / 1000;
        Time::framePerSec = Time::frames;
        Time::frames = 0;
        Time::avgFrame = Time::passedFrames / (float)++Time::passedTime;
    }

    Time::pastTime = iTime;
}

void Game::InputBufferReset()
{
    for (int i = MouseInput::LBUTTONCLK; i < MouseInput::END; ++i)
    {
        if (GetInputBuffer(g_mouse, (MouseInput)i)) SetInputBuffer(g_mouse, (MouseInput)i, false);
    }
    g_key.clear();
}

void Game::Start()
{
    for (int i = 0; i < g_Objects.size(); ++i)
    {
        if (g_Objects[i]->isActive() && !g_Objects[i]->isStarted()) g_Objects[i]->Start();
    }
}

void Game::Update()
{
    if (g_RootObject != nullptr) g_RootObject->Update();
    if (g_RootRectObject != nullptr) g_RootRectObject->Update();
}

void Game::ComponentRegister()
{
    ComponentManager::RegisterComponent<Animator>("Animator");
    ComponentManager::RegisterComponent<BoxCollider>("BoxCollider");
    ComponentManager::RegisterComponent<Camera>("Camera");
    ComponentManager::RegisterComponent<MeshRenderer>("MeshRenderer");
    ComponentManager::RegisterComponent<MouseFunction>("MouseFunction");
    ComponentManager::RegisterComponent<RectTransform>("RectTransform");
    ComponentManager::RegisterComponent<SphereCollider>("SphereCollider");
    ComponentManager::RegisterComponent<SpriteRenderer>("SpriteRenderer");
    ComponentManager::RegisterComponent<TextRenderer>("TextRenderer");
    ComponentManager::RegisterComponent<Transform>("Transform");
    ComponentManager::RegisterComponent<VerticeRenderer>("VerticeRenderer");
}