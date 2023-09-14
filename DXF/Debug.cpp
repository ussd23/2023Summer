#include "resource.h"
#include "DXHeader.h"
#include "Global.h"
#include "Functions.h"
#include "GameObject.h"
#include "ComponentHeader.h"

map<int, HWND> DebugHandles::m_HandlesMap;

HWND DebugHandles::GetHandle(int p_Resource)
{
    map<int, HWND>::iterator iter = m_HandlesMap.find(p_Resource);
    if (iter != m_HandlesMap.end())
    {
        return iter->second;
    }
    
    HWND handle = NULL;
    handle = GetDlgItem(DXFGame::m_hDlg, p_Resource);
    if (handle != NULL)
    {
        m_HandlesMap.insert(make_pair(p_Resource, handle));
        return handle;
    }
    else
    {
        return NULL;
    }
}

void DXFGame::DebugUpdate()
{
	if (!(m_DebugUpdate && m_DebugUpdateTerm > 0.1f))
	{
		m_DebugUpdate = true;
		return;
	}
	m_DebugUpdate = false;
	m_DebugUpdateTerm = 0;

	HWND tree = DebugHandles::GetHandle(IDC_HierarchyTree);

	Var::DebugObjectMap.clear();
	TreeView_DeleteAllItems(tree);

	if (m_HTab == 0)
	{
		Var::RootObject->DebugInsert(tree, TVI_ROOT);
	}
	else if (m_HTab == 1)
	{
		Var::RootRectObject->DebugInsert(tree, TVI_ROOT);
	}

    if (GameObject::Exists(Var::DebugSelected))
    {
        TreeView_SelectItem(tree, Var::DebugHandle);
    }
    else
    {
        ResetSelected();
    }
}

void DXFGame::DebugCheck()
{
	if (m_DebugUpdate)
	{
		m_DebugUpdateTerm += Time::deltaTime;
		DebugUpdate();
	}
}

INT_PTR WINAPI DXFGame::DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_Create:
        {
            if (m_HTab == 0)
            {
                Vector3 pos = Vector3(0, 0, 0);
                if (Var::DebugSelected != nullptr)
                {
                    Transform* transform = GetComponentFromObject(Var::DebugSelected, Transform);
                    pos = transform->GetWorldPosition();
                }
                GameObject* gameObject = new EmptyObject("New Empty Object", pos);
            }
            else if (m_HTab == 1)
            {
                Vector2 pos = Vector2(50, 50);
                Vector2 size = Vector2(100, 100);
                if (Var::DebugSelected != nullptr)
                {
                    RectTransform* recttransform = GetComponentFromObject(Var::DebugSelected, RectTransform);
                    pos = recttransform->GetScreenPosition();
                }
                GameObject* gameObject = new EmptyRectObject("New Empty Object", size, pos);
            }
        }
        break;
        case IDC_Duplicate:
        {
            if (Var::DebugSelected != nullptr)
            {
                GameObject::Instantiate(Var::DebugSelected);
            }
        }
        break;
        case IDC_Destroy:
        {
            if (Var::DebugSelected != nullptr)
            {
                GameObject::Destroy(Var::DebugSelected);
            }
        }
        break;
        case IDC_Active:
        {
            if (HIWORD(wParam) == BN_CLICKED && Var::DebugSelected != nullptr)
            {
                BOOL isChecked = SendMessage(DebugHandles::GetHandle(IDC_Active), BM_GETCHECK, 0, 0);
                if (isChecked == BST_CHECKED)
                {
                    Var::DebugSelected->SetActive(true);
                }
                else
                {
                    Var::DebugSelected->SetActive(false);
                }
            }
        }
        break;
        case IDC_Name:
        {
            if (HIWORD(wParam) == EN_CHANGE && Var::DebugSelected != nullptr)
            {
                BOOL isChecked = SendMessage(DebugHandles::GetHandle(IDC_Name), LB_GETCURSEL, 0, 0);
                if (isChecked >= 0)
                {
                    char buf[256];
                    GetDlgItemText(m_hDlg, IDC_Name, buf, 255);
                    Var::DebugSelected->m_Name = buf;

                    TV_ITEM tvItem;
                    ZeroMemory(&tvItem, sizeof(TV_ITEM));
                    tvItem.hItem = Var::DebugHandle;
                    tvItem.mask = TVIF_TEXT;
                    string itemname = "¡¤ " + string(buf);
                    tvItem.pszText = const_cast<char*>(itemname.c_str());
                    TreeView_SetItem(DebugHandles::GetHandle(IDC_HierarchyTree), &tvItem);
                }
            }
        }
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
                m_HTab = TabCtrl_GetCurFocus(DebugHandles::GetHandle(IDC_Hierarchy));

                ResetSelected();
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
                TreeView_GetItem(DebugHandles::GetHandle(IDC_HierarchyTree), &item);

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

            else if (nmhdr->code == TVN_SELCHANGED)
            {
                NM_TREEVIEW* pnmTreeView = (NM_TREEVIEW*)lParam;
                HTREEITEM hItem = pnmTreeView->itemNew.hItem;
                TVITEM item;
                item.mask = TVIF_HANDLE;
                item.hItem = pnmTreeView->itemNew.hItem;
                TreeView_GetItem(DebugHandles::GetHandle(IDC_HierarchyTree), &item);

                map<HTREEITEM, GameObject*>::iterator iter = Var::DebugObjectMap.find(hItem);

                if (Var::DebugObjectMap.find(hItem) != Var::DebugObjectMap.end())
                {
                    GameObject* obj = iter->second;

                    if (obj != nullptr)
                    {
                        Var::DebugHandle = iter->first;
                        Var::DebugSelected = obj;

                        ChangeSelected();
                    }
                }
            }

            if (Var::DebugSelected != nullptr)
            {
                EnableWindow(DebugHandles::GetHandle(IDC_Duplicate), true);
                EnableWindow(DebugHandles::GetHandle(IDC_Destroy), true);
                EnableWindow(DebugHandles::GetHandle(IDC_Active), true);
                EnableWindow(DebugHandles::GetHandle(IDC_Name), true);
            }
            else
            {
                EnableWindow(DebugHandles::GetHandle(IDC_Duplicate), false);
                EnableWindow(DebugHandles::GetHandle(IDC_Destroy), false);
                EnableWindow(DebugHandles::GetHandle(IDC_Active), false);
                EnableWindow(DebugHandles::GetHandle(IDC_Name), false);
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

void DXFGame::ResetSelected()
{
    Var::DebugHandle = NULL;
    Var::DebugSelected = nullptr;

    SendMessage(DebugHandles::GetHandle(IDC_Active), BM_SETCHECK, BST_UNCHECKED, 0);
    SetWindowText(DebugHandles::GetHandle(IDC_Name), "");
}

void DXFGame::ChangeSelected()
{
    if (Var::DebugSelected == nullptr)
    {
        ResetSelected();
        return;
    }

    if (Var::DebugSelected->isActive())
    {
        SendMessage(DebugHandles::GetHandle(IDC_Active), BM_SETCHECK, BST_CHECKED, 0);
    }
    else
    {
        SendMessage(DebugHandles::GetHandle(IDC_Active), BM_SETCHECK, BST_UNCHECKED, 0);
    }

    SetWindowText(DebugHandles::GetHandle(IDC_Name), Var::DebugSelected->m_Name.c_str());
}