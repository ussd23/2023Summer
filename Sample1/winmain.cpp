#define WINMAIN
#include "DXHeader.h"
#include "Global.h"
#include "GameObject.h"
#include "Sample.h"

INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
    UNREFERENCED_PARAMETER(hInst);
    srand(time(NULL));

    WNDCLASSEX wc =
    {
        sizeof(WNDCLASSEX), CS_CLASSDC, Sample1::MsgProc, 0L, 0L,
        GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
        "DXF", NULL
    };
    RegisterClassEx(&wc);

    HWND hWnd = CreateWindow("DXF", "DXF Sample",
        WS_OVERLAPPEDWINDOW, 100, 100, SCREENSIZEX + 16, SCREENSIZEY + 39,
        NULL, NULL, wc.hInstance, NULL);

    if (SUCCEEDED(Sample1::InitD3D(hWnd)))
    {
        ShowWindow(hWnd, SW_SHOWDEFAULT);
        UpdateWindow(hWnd);

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

    UnregisterClass("DXF", wc.hInstance);
    Sample1::Cleanup();
    return 0;
}