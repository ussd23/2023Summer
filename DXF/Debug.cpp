#include "resource.h"
#include "DXHeader.h"
#include "Global.h"
#include "Functions.h"
#include "GameObject.h"
#include "ComponentHeader.h"

void DXFGame::DebugUpdate()
{
	if (!m_DebugMode) return;

	if (!(m_DebugUpdate && m_DebugUpdateTerm > 0.1f))
	{
		m_DebugUpdate = true;
		return;
	}
	m_DebugUpdate = false;
	m_DebugUpdateTerm = 0;

	HWND tree = GetDlgItem(m_hDlg, IDC_HierarchyTree);

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

    if (!GameObject::Exists(Var::DebugSelected))
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
            if (HIWORD(wParam) == BN_CLICKED)
            {
                HWND hCheckBox = GetDlgItem(m_hDlg, IDC_Active);
                BOOL isChecked = SendMessage(hCheckBox, BM_GETCHECK, 0, 0);
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

            else if (nmhdr->code == TVN_SELCHANGED)
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
                        Var::DebugSelected = obj;

                        ChangeSelected();
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

void DXFGame::ResetSelected()
{
    Var::DebugSelected = nullptr;

    HWND check = GetDlgItem(m_hDlg, IDC_Active);
    SendMessage(check, BM_SETCHECK, BST_UNCHECKED, 0);

    HWND edit = GetDlgItem(m_hDlg, IDC_Name);
    SetWindowText(edit, "");
}

void DXFGame::ChangeSelected()
{
    if (Var::DebugSelected == nullptr)
    {
        ResetSelected();
        return;
    }

    HWND check = GetDlgItem(m_hDlg, IDC_Active);
    if (Var::DebugSelected->isActive())
    {
        SendMessage(check, BM_SETCHECK, BST_CHECKED, 0);
    }
    else
    {
        SendMessage(check, BM_SETCHECK, BST_UNCHECKED, 0);
    }

    HWND edit = GetDlgItem(m_hDlg, IDC_Name);
    SetWindowText(edit, Var::DebugSelected->m_Name.c_str());
}