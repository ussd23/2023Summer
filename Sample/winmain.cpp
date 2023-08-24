#define WINMAIN
#include "DXHeader.h"
#include "Global.h"
#include "GameObject.h"
#include "Sample.h"

INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
    Sample::m_Resolution = Vector2(1280, 720);

    if (SUCCEEDED(Sample::InitD3D(hInst)))
    {
        Sample::ComponentRegister();
        Sample::ScriptRegister();

        Sample::InitObject();

        while (Sample::m_Msg.message != WM_QUIT)
        {
            // Frame Update
            Input::InputBufferReset();
            Time::TimeUpdate();

            // Message
            Sample::Message();

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