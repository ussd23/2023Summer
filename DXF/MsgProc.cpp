#include "DXHeader.h"
#include "Functions.h"
#include "Global.h"
#include "Raycast.h"

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_KEYDOWN:
        SetInputBuffer(g_key, wParam, true);
        SetInputBuffer(g_keyhold, wParam, true);
        return 0;

    case WM_KEYUP:
        SetInputBuffer(g_keyhold, wParam, false);
        return 0;

    case WM_LBUTTONDOWN:
        SetInputBuffer(g_mouse, MouseInput::LBUTTONHOLD, true);
        SetInputBuffer(g_mouse, MouseInput::LBUTTONCLK, true);
        return 0;

    case WM_LBUTTONUP:
        SetInputBuffer(g_mouse, MouseInput::LBUTTONHOLD, false);
        return 0;

    case WM_RBUTTONDOWN:
        SetInputBuffer(g_mouse, MouseInput::RBUTTONHOLD, true);
        SetInputBuffer(g_mouse, MouseInput::RBUTTONCLK, true);
        return 0;

    case WM_RBUTTONUP:
        SetInputBuffer(g_mouse, MouseInput::RBUTTONHOLD, false);
        return 0;

    case WM_MBUTTONDOWN:
        SetInputBuffer(g_mouse, MouseInput::MBUTTONHOLD, true);
        SetInputBuffer(g_mouse, MouseInput::MBUTTONCLK, true);
        return 0;

    case WM_MBUTTONUP:
        SetInputBuffer(g_mouse, MouseInput::MBUTTONHOLD, false);
        return 0;

    case WM_MOUSEMOVE:
        g_mousepos.x = LOWORD(lParam);
        g_mousepos.y = HIWORD(lParam);
        g_mouseraycast = Raycast::ScreenToWorld(g_mousepos);
        return 0;

    case WM_MOUSEWHEEL:
        if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) SetInputBuffer(g_mouse, MouseInput::WHEELUP, true);
        if (GET_WHEEL_DELTA_WPARAM(wParam) < 0) SetInputBuffer(g_mouse, MouseInput::WHEELDOWN, true);
        return 0;

    case WM_DESTROY:
        Cleanup();
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}
