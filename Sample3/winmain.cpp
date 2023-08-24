#define WINMAIN
#include "DXHeader.h"
#include "Global.h"
#include "GameObject.h"
#include "Sample3.h"

INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
    Sample3::m_Title = "Mine";
    Sample3::m_Resolution = Vector2(900, 900);

    if (SUCCEEDED(Sample3::InitD3D(hInst)))
    {
        Sample3::ComponentRegister();
        Sample3::ScriptRegister();

        Sample3::InitObject();

        MSG msg;
        ZeroMemory(&msg, sizeof(msg));
        while (msg.message != WM_QUIT)
        {
            // Frame Update
            Input::InputBufferReset();
            Time::TimeUpdate();

            // Message
            Sample3::Message(&msg);

            // Start
            Sample3::Start();

            // Update
            Sample3::Update();

            // Render
            if (FAILED(Sample3::Render())) break;

            // SafeDestroy
            GameObject::SafeDestroy();
        }
    }

    Sample3::Cleanup();
    return 0;
}