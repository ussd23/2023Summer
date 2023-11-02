#define WINMAIN
#include "DXHeader.h"
#include "Global.h"
#include "GameObject.h"
#include "Sample_UI.h"

INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
    Sample_UI::m_Resolution = Vector2(1280, 720);
    Sample_UI::m_DebugMode = true;

    if (SUCCEEDED(Sample_UI::InitD3D(hInst)))
    {
        Sample_UI::ComponentRegister();
        Sample_UI::ScriptRegister();

        Sample_UI::InitObject();

        while (Sample_UI::m_Msg.message != WM_QUIT)
        {
            // Frame Update
            Input::InputBufferReset();
            Time::TimeUpdate();

            // Message
            Sample_UI::Message();

            // Start
            Sample_UI::Start();

            // Update
            Sample_UI::Update();

            // Render
            if (FAILED(Sample_UI::Render())) break;

            // SafeDestroy
            GameObject::SafeDestroy();
        }
    }

    Sample_UI::Cleanup();
    return 0;
}