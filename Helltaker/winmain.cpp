#define WINMAIN
#include "DXHeader.h"
#include "Global.h"
#include "GameObject.h"

INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
    UNREFERENCED_PARAMETER(hInst);
    srand(time(NULL));

    WNDCLASSEX wc =
    {
        sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
        "DXF", NULL
    };
    RegisterClassEx(&wc);

    HWND hWnd = CreateWindow("DXF", "DXF Sample",
        WS_OVERLAPPEDWINDOW, 100, 100, SCREENSIZEX + 16, SCREENSIZEY + 39,
        NULL, NULL, wc.hInstance, NULL);

    if (SUCCEEDED(InitD3D(hWnd)))
    {
        g_pd3dDevice->GetMaterial(&g_defaultMaterial);
        g_pd3dDevice->GetTexture(0, &g_defaultTexture);

        ShowWindow(hWnd, SW_SHOWDEFAULT);
        UpdateWindow(hWnd);
        Game::InitObject();

        MSG msg;
        ZeroMemory(&msg, sizeof(msg));
        while (msg.message != WM_QUIT)
        {
            // Frame Update
            Game::InputBufferReset();
            Game::TimeUpdate();

            // Message
            if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

            // Start
            Game::Start();

            // Update
            Game::Update();

            // Render
            if (FAILED(Render())) break;

            // SafeDestroy
            GameObject::SafeDestroy();
        }
    }

    UnregisterClass("DXF", wc.hInstance);
    return 0;
}