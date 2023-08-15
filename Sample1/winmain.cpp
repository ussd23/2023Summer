#define WINMAIN
#include "DXHeader.h"
#include "Global.h"
#include "GameObject.h"
#include "Sample.h"

INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
    Sample1::m_Title = "DXF Flight";
    Sample1::m_Resolution = Vector2(1600, 900);

    if (SUCCEEDED(Sample1::InitD3D(hInst)))
    {
        ShowWindow(Sample1::m_hWnd, SW_SHOWDEFAULT);
        UpdateWindow(Sample1::m_hWnd);

        Sample1::ComponentRegister();
        Sample1::ScriptRegister();

        Sample1::InitObject();

        MSG msg;
        ZeroMemory(&msg, sizeof(msg));
        while (msg.message != WM_QUIT)
        {
            // Frame Update
            Input::InputBufferReset();
            Time::TimeUpdate();

            // Message
            if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

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

    UnregisterClass("DXF", Sample1::m_WndClass.hInstance);
    Sample1::Cleanup();
    return 0;
}