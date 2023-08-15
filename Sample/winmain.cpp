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
        ShowWindow(Sample::m_hWnd, SW_SHOWDEFAULT);
        UpdateWindow(Sample::m_hWnd);

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
            if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

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

    UnregisterClass("DXF", Sample::m_WndClass.hInstance);
    Sample::Cleanup();
    return 0;
}