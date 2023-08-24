#define WINMAIN
#include "DXHeader.h"
#include "Global.h"
#include "GameObject.h"
#include "PuzzleBobble.h"

INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
    PuzzleBobble::m_Title = "DXF PuzzleBobble";
    PuzzleBobble::m_Resolution = Vector2(600, 900);

    if (SUCCEEDED(PuzzleBobble::InitD3D(hInst)))
    {
        PuzzleBobble::ComponentRegister();
        PuzzleBobble::ScriptRegister();

        PuzzleBobble::InitObject();

        MSG msg;
        ZeroMemory(&msg, sizeof(msg));
        while (msg.message != WM_QUIT)
        {
            // Frame Update
            Input::InputBufferReset();
            Time::TimeUpdate();

            // Message
            PuzzleBobble::Message(&msg);

            // Start
            PuzzleBobble::Start();

            // Update
            PuzzleBobble::Update();

            // Render
            if (FAILED(PuzzleBobble::Render())) break;

            // SafeDestroy
            GameObject::SafeDestroy();
        }
    }

    PuzzleBobble::Cleanup();
    return 0;
}