#include "resource.h"
#include "DXHeader.h"
#include "Functions.h"
#include "Global.h"
#include "Raycast.h"

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
        SetWindowPos(hWnd, NULL, 0, 0, m_Resolution.x + 16, m_Resolution.y + 39, SWP_NOMOVE | SWP_NOZORDER);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

INT_PTR WINAPI DXFGame::DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_INITDIALOG:
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 0:
            MessageBox(NULL, "Dialog", "Button1", MB_OK);
            break;
        }
        return TRUE;

    case WM_NOTIFY:
    {
        LPNMHDR nmhdr = (LPNMHDR)lParam;

        if (wParam == IDC_Hierarchy)
        {
            if (nmhdr->code == TCN_SELCHANGE)
            {
                HWND tabctrl = GetDlgItem(m_hDlg, IDC_Hierarchy);
                m_HTab = TabCtrl_GetCurFocus(tabctrl);

                DebugUpdate();
            }
        }
        else if (wParam == IDC_HierarchyTree)
        {
            if (nmhdr->code == TVN_ITEMEXPANDED)
            {
                NM_TREEVIEW* pnmTreeView = (NM_TREEVIEW*)lParam;
                HTREEITEM hItem = pnmTreeView->itemNew.hItem;
                TVITEM item;
                item.mask = TVIF_HANDLE;
                item.hItem = pnmTreeView->itemNew.hItem;
                HWND tree = GetDlgItem(m_hDlg, IDC_HierarchyTree);
                TreeView_GetItem(tree, &item);

                map<HTREEITEM, GameObject*>::iterator iter = Var::DebugObjectMap.find(hItem);

                if (Var::DebugObjectMap.find(hItem) != Var::DebugObjectMap.end())
                {
                    GameObject* obj = iter->second;

                    if (obj != nullptr)
                    {
                        if (item.state & TVIS_EXPANDED)
                        {
                            obj->m_DebugExtended = true;
                        }
                        else
                        {
                            obj->m_DebugExtended = false;
                        }
                    }
                }
            }
        }
    }
        return TRUE;

    case WM_DESTROY:
        DestroyWindow(hDlg);
        hDlg = NULL;
        return TRUE;
    }

    return FALSE;
}
