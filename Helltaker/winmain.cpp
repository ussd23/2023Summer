#define WINMAIN
#include "DXHeader.h"
#include "Global.h"
#include "GameObject.h"
#include "Helltaker.h"

INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
    UNREFERENCED_PARAMETER(hInst);
    srand(time(NULL));

    WNDCLASSEX wc =
    {
        sizeof(WNDCLASSEX), CS_CLASSDC, Helltaker::MsgProc, 0L, 0L,
        GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
        "DXF", NULL
    };
    RegisterClassEx(&wc);

    HWND hWnd = CreateWindow("DXF", "DXF Sample",
        WS_OVERLAPPEDWINDOW, 100, 100, SCREENSIZEX + 16, SCREENSIZEY + 39,
        NULL, NULL, wc.hInstance, NULL);

    if (SUCCEEDED(Helltaker::InitD3D(hWnd)))
    {
        ShowWindow(hWnd, SW_SHOWDEFAULT);
        UpdateWindow(hWnd);
        Helltaker::InitObject();

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
            Helltaker::Start();

            // Update
            Helltaker::Update();

            // Render
            if (FAILED(Helltaker::Render())) break;

            // SafeDestroy
            GameObject::SafeDestroy();
        }
    }

    UnregisterClass("DXF", wc.hInstance);
    return 0;
}