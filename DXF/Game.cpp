#include "DXHeader.h"
#include "Global.h"
#include "Functions.h"
#include "GameObject.h"

UINT Time::pastTime = 0;
int Time::sec = 0;
int Time::frames = 0;
int Time::passedFrames = 0;
int Time::passedTime = 0;

void DXFGame::InputBufferReset()
{
    for (int i = MouseInput::LBUTTONDOWN; i < MouseInput::END; ++i)
    {
        if (GetInputBuffer(g_mouse, (MouseInput)i)) SetInputBuffer(g_mouse, (MouseInput)i, false);
    }
    g_key.clear();
}

void DXFGame::Start()
{
    for (int i = 0; i < g_NewComponents.size(); ++i)
    {
        g_NewComponents[i]->Start();
    }
    g_NewComponents.clear();
}

void DXFGame::Update()
{
    if (g_RootObject != nullptr) g_RootObject->Update();
    if (g_RootRectObject != nullptr) g_RootRectObject->Update();
}