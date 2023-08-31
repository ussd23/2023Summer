#define WINMAIN
#include "DXHeader.h"
#include "Global.h"
#include "GameObject.h"
#include "Sample.h"

INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
    Sample1::m_Title = "DXF Flight";
    Sample1::m_Resolution = Vector2(1600, 900);
    Sample1::m_DebugMode = true;

    if (SUCCEEDED(Sample1::InitD3D(hInst)))
    {
        Sample1::ComponentRegister();
        Sample1::ScriptRegister();

        Sample1::InitObject();

        while (Sample1::m_Msg.message != WM_QUIT)
        {
            // Frame Update
            Input::InputBufferReset();
            Time::TimeUpdate();

            // Message
            Sample1::Message();

            // Start
            Sample1::Start();

            // Update
            Sample1::Update();

            // Render
            if (FAILED(Sample1::Render())) break;

            // SafeDestroy
            GameObject::SafeDestroy();
        }
    }

    Sample1::Cleanup();
    return 0;
}