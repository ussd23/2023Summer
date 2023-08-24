#define WINMAIN
#include "DXHeader.h"
#include "Global.h"
#include "GameObject.h"
#include "Sample.h"

INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
    Sample::m_Resolution = Vector2(1600, 900);

    if (SUCCEEDED(Sample::InitD3D(hInst)))
    {
        Sample::ComponentRegister();
        Sample::ScriptRegister();

        Sample::InitObject();

        MSG msg;
        ZeroMemory(&msg, sizeof(msg));
        while (msg.message != WM_QUIT)
        {
            // Frame Update
            Input::InputBufferReset();
            Time::TimeUpdate();

            // Message
            Sample::Message(&msg);

            // Start
            Sample::Start();

            // Update
            Sample::Update();

            // Render
            if (FAILED(Sample::Render())) break;

            // SafeDestroy
            GameObject::SafeDestroy();
        }
    }

    Sample::Cleanup();
    return 0;
}