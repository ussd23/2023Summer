#include "resource.h"
#include "DXHeader.h"
#include "Functions.h"
#include "Global.h"
#include "Raycast.h"
#include "FontManager.h"

LRESULT WINAPI DXFGame::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_KEYDOWN:
        SetInputBuffer(Key, wParam, true);
        SetInputBuffer(KeyHold, wParam, true);
        return 0;

    case WM_KEYUP:
        SetInputBuffer(KeyHold, wParam, false);
        return 0;

    case WM_LBUTTONDOWN:
        SetInputBuffer(Mouse, MouseInput::LBUTTONHOLD, true);
        SetInputBuffer(Mouse, MouseInput::LBUTTONDOWN, true);
        return 0;

    case WM_LBUTTONUP:
        SetInputBuffer(Mouse, MouseInput::LBUTTONHOLD, false);
        SetInputBuffer(Mouse, MouseInput::LBUTTONUP, true);
        return 0;

    case WM_RBUTTONDOWN:
        SetInputBuffer(Mouse, MouseInput::RBUTTONHOLD, true);
        SetInputBuffer(Mouse, MouseInput::RBUTTONDOWN, true);
        return 0;

    case WM_RBUTTONUP:
        SetInputBuffer(Mouse, MouseInput::RBUTTONHOLD, false);
        SetInputBuffer(Mouse, MouseInput::RBUTTONUP, true);
        return 0;

    case WM_MBUTTONDOWN:
        SetInputBuffer(Mouse, MouseInput::MBUTTONHOLD, true);
        SetInputBuffer(Mouse, MouseInput::MBUTTONDOWN, true);
        return 0;

    case WM_MBUTTONUP:
        SetInputBuffer(Mouse, MouseInput::MBUTTONHOLD, false);
        SetInputBuffer(Mouse, MouseInput::MBUTTONUP, true);
        return 0;

    case WM_MOUSEMOVE:
        Input::MousePosition.x = LOWORD(lParam);
        Input::MousePosition.y = HIWORD(lParam);
        Input::MouseRaycast = Raycast::ScreenToWorld(Input::MousePosition);
        return 0;

    case WM_MOUSEWHEEL:
        if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) SetInputBuffer(Mouse, MouseInput::WHEELUP, true);
        if (GET_WHEEL_DELTA_WPARAM(wParam) < 0) SetInputBuffer(Mouse, MouseInput::WHEELDOWN, true);
        return 0;

    case WM_SIZE:
        if (wParam != SIZE_MINIMIZED)
        {
            m_Resolution.x = LOWORD(lParam);
            m_Resolution.y = HIWORD(lParam);
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}