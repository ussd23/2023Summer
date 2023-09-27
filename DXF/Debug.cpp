#include "resource.h"
#include "DXHeader.h"
#include "Global.h"
#include "Functions.h"
#include "GameObject.h"
#include "ComponentHeader.h"

#define EDIT_POSITION_X_KEY 360
#define EDIT_POSITION_X_VALUE 440
#define EDIT_POSITION_Y_KEY 69
#define EDIT_POSITION_Y_VALUE 67
#define EDIT_WIDTH_KEY 78
#define EDIT_WIDTH_VALUE 220
#define EDIT_HEIGHT 18
#define EDIT_INTERVAL_WIDTH 20
#define EDIT_INTERVAL_HEIGHT 22
#define EDIT_HEIGHT_LIMIT 23

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
    else if (m_HTab == 2)
    {
        if (Var::RootObject != nullptr) Var::RootObject->DebugInsert(tree, TVI_ROOT);
        if (Var::RootRectObject != nullptr) Var::RootRectObject->DebugInsert(tree, TVI_ROOT);
    }

    if (GameObject::Exists(Var::DebugSelected))
    {
        TreeView_SelectItem(tree, Var::DebugHandle);
    }
    else
    {
        ResetSelected();
        ResetComponent();
    }
}

void DXFGame::DebugCheck()
{
	if (m_DebugUpdate)
	{
		m_DebugUpdateTerm += Time::deltaTime;
		DebugUpdate();
	}

    if (GameObject::Exists(Var::DebugSelected))
    {
        if (Var::DebugComponent != nullptr)
        {
            UpdateHandles();
        }
    }
    else
    {
        ResetSelected();
        ResetComponent();
    }
}

INT_PTR WINAPI DXFGame::DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_MOUSEWHEEL:
        if (Var::DebugComponent != nullptr)
        {
            int currentIndex = Var::DebugInspectorIndex;

            if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
            {
                if (Var::DebugInspectorIndex < 0) ++Var::DebugInspectorIndex;
            }

            if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
            {
                if (Var::DebugInspectorIndex > -Var::DebugInspectorMaxIndex + EDIT_HEIGHT_LIMIT) --Var::DebugInspectorIndex;
            }

            if (currentIndex == Var::DebugInspectorIndex) return TRUE;

            vector<pair<HWND, Vector2>>::iterator iter = Var::DebugHandleStatics.begin();
            while (iter != Var::DebugHandleStatics.end())
            {
                if (iter->second.y + Var::DebugInspectorIndex >= 0 &&
                    iter->second.y + Var::DebugInspectorIndex < EDIT_HEIGHT_LIMIT)
                {
                    ShowWindow(iter->first, SW_SHOW);
                    SetWindowPos(iter->first, NULL,
                        EDIT_POSITION_X_KEY + EDIT_INTERVAL_WIDTH * iter->second.x, EDIT_POSITION_Y_KEY + EDIT_INTERVAL_HEIGHT * (iter->second.y + Var::DebugInspectorIndex),
                        0, 0, SWP_NOSIZE | SWP_NOZORDER);
                    RedrawWindow(iter->first, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
                }
                else
                {
                    ShowWindow(iter->first, SW_HIDE);
                }

                ++iter;
            }

            iter = Var::DebugHandleEdits.begin();
            while (iter != Var::DebugHandleEdits.end())
            {
                if (iter->second.y + Var::DebugInspectorIndex >= 0 &&
                    iter->second.y + Var::DebugInspectorIndex < EDIT_HEIGHT_LIMIT)
                {
                    ShowWindow(iter->first, SW_SHOW);
                    SetWindowPos(iter->first, NULL,
                        EDIT_POSITION_X_VALUE + EDIT_INTERVAL_WIDTH * iter->second.x, EDIT_POSITION_Y_VALUE + EDIT_INTERVAL_HEIGHT * (iter->second.y + Var::DebugInspectorIndex),
                        0, 0, SWP_NOSIZE | SWP_NOZORDER);
                    RedrawWindow(iter->first, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
                }
                else
                {
                    ShowWindow(iter->first, SW_HIDE);
                }

                ++iter;
            }
        }
    return TRUE;
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
        case IDC_Pause:
        {
            Time::paused = !Time::paused;

            if (Time::paused)
            {
                SetWindowText(DebugHandles::GetHandle(IDC_Pause), "¢º Play");
            }
            else
            {
                SetWindowText(DebugHandles::GetHandle(IDC_Pause), "ll Pause");
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
                HWND handle = DebugHandles::GetHandle(IDC_Hierarchy);

                SetFocus(handle);
                m_HTab = TabCtrl_GetCurFocus(handle);

                ResetSelected();
                ResetHandles();
                DebugUpdate();
            }
        }

        else if (wParam == IDC_HierarchyTree)
        {
            GameObject* pastObject = Var::DebugSelected;

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

            if (Var::DebugSelected == nullptr)
            {
                EnableWindow(DebugHandles::GetHandle(IDC_Duplicate), false);
                EnableWindow(DebugHandles::GetHandle(IDC_Destroy), false);
                EnableWindow(DebugHandles::GetHandle(IDC_Active), false);
                EnableWindow(DebugHandles::GetHandle(IDC_Name), false);

                ResetComponent();
            }

            else if (pastObject != Var::DebugSelected)
            {
                EnableWindow(DebugHandles::GetHandle(IDC_Duplicate), true);
                EnableWindow(DebugHandles::GetHandle(IDC_Destroy), true);
                EnableWindow(DebugHandles::GetHandle(IDC_Active), true);
                EnableWindow(DebugHandles::GetHandle(IDC_Name), true);

                ResetComponent();

                HWND tab = DebugHandles::GetHandle(IDC_Inspector);

                list<SPTR<Component>>::iterator iter = Var::DebugSelected->m_Components.begin();

                for (int i = 0; iter != Var::DebugSelected->m_Components.end(); ++i)
                {
                    Component* comp = (*iter++)();
                    string str = typeid(*comp).name();
                    str = str.substr(6);

                    TCITEMA tItem;
                    tItem.mask = TCIF_TEXT;
                    tItem.pszText = const_cast<char*>(str.c_str());
                    TabCtrl_InsertItem(tab, i, &tItem);
                }

                UpdateComponent(0);
            }
        }

        else if (wParam == IDC_Inspector)
        {
            if (nmhdr->code == TCN_SELCHANGE)
            {
                HWND handle = DebugHandles::GetHandle(IDC_Inspector);

                SetFocus(handle);
                int tab = TabCtrl_GetCurFocus(handle);

                UpdateComponent(tab);
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

void DXFGame::UpdateComponent(int p_Index)
{
    ResetHandles();

    if (Var::DebugSelected == nullptr) return;

    Var::DebugComponent = Var::DebugSelected->GetComponent(p_Index);

    if (Var::DebugComponent == nullptr) return;

    Var::DebugJson.clear();
    Var::DebugComponent->JsonSerialize(Var::DebugJson);

    int gridX = 0;
    int gridY = 0;

    CreateDebugHandles(&Var::DebugJson, gridX, gridY, false, false);
    m_HandleUpdateTerm = 0;
    Var::DebugInspectorMaxIndex = gridY;
}

void DXFGame::ResetComponent()
{
    HWND tab = DebugHandles::GetHandle(IDC_Inspector);

    int tabCount = TabCtrl_GetItemCount(tab);
    for (int i = tabCount - 1; i >= 0; --i)
    {
        TabCtrl_DeleteItem(tab, i);
    }

    Var::DebugComponent = nullptr;
}

void DXFGame::CreateDebugHandles(Json::Value* p_JsonValue, int& p_GridX, int& p_GridY, bool p_isArray, bool p_isUpdate)
{
    if (p_isArray)
    {
        for (unsigned int i = 0; i < p_JsonValue->size(); ++i)
        {
            Json::Value* value = &(*p_JsonValue)[i];

            if (!p_isUpdate)
            {
                stringstream ss;
                ss << "[" << i << "]";
                HWND hwndEdit = CreateWindow("STATIC", ss.str().c_str(), WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN | ES_AUTOHSCROLL | SS_ENDELLIPSIS,
                    EDIT_POSITION_X_KEY + EDIT_INTERVAL_WIDTH * p_GridX, EDIT_POSITION_Y_KEY + EDIT_INTERVAL_HEIGHT * p_GridY,
                    EDIT_WIDTH_KEY, EDIT_HEIGHT, m_hDlg, NULL, m_WndClass.hInstance, NULL);
                SendMessage(hwndEdit, WM_SETFONT, (WPARAM)m_hFont, TRUE);
                RedrawWindow(hwndEdit, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
                if (p_GridY >= EDIT_HEIGHT_LIMIT) ShowWindow(hwndEdit, SW_HIDE);

                Var::DebugHandleStatics.push_back(make_pair(hwndEdit, Vector2(p_GridX, p_GridY)));
            }

            InnerCreateDebugHandles(value, p_GridX, p_GridY, p_isArray, p_isUpdate);
        }
    }
    else
    {
        for (string member : p_JsonValue->getMemberNames())
        {
            if (member == "m_ChildID") continue;

            Json::Value* value = &(*p_JsonValue)[member];

            if (!p_isUpdate)
            {
                HWND hwndEdit = CreateWindow("STATIC", member.c_str(), WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN | ES_AUTOHSCROLL | SS_ENDELLIPSIS,
                    EDIT_POSITION_X_KEY + EDIT_INTERVAL_WIDTH * p_GridX, EDIT_POSITION_Y_KEY + EDIT_INTERVAL_HEIGHT * p_GridY,
                    EDIT_WIDTH_KEY, EDIT_HEIGHT, m_hDlg, NULL, m_WndClass.hInstance, NULL);
                SendMessage(hwndEdit, WM_SETFONT, (WPARAM)m_hFont, TRUE);
                RedrawWindow(hwndEdit, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
                if (p_GridY >= EDIT_HEIGHT_LIMIT) ShowWindow(hwndEdit, SW_HIDE);

                Var::DebugHandleStatics.push_back(make_pair(hwndEdit, Vector2(p_GridX, p_GridY)));
            }

            InnerCreateDebugHandles(value, p_GridX, p_GridY, p_isArray, p_isUpdate);
        }
    }
}

void DXFGame::InnerCreateDebugHandles(Json::Value* p_JsonValue, int& p_GridX, int& p_GridY, bool p_isArray, bool p_isUpdate)
{
    if (p_JsonValue->isObject())
    {
        CreateDebugHandles(p_JsonValue, ++p_GridX, p_isArray ? p_GridY : ++p_GridY, false, p_isUpdate);
        --p_GridX;
    }
    else if (p_JsonValue->isArray())
    {
        CreateDebugHandles(p_JsonValue, ++p_GridX, p_isArray ? p_GridY : ++p_GridY, true, p_isUpdate);
        --p_GridX;
    }
    else
    {
        if (p_JsonValue->isNull())
        {
            if (!p_isUpdate)
            {
                HWND hwndEdit = CreateWindow("EDIT", "", WS_VISIBLE | WS_BORDER | WS_CHILD | WS_CLIPCHILDREN | ES_AUTOHSCROLL,
                    EDIT_POSITION_X_VALUE + EDIT_INTERVAL_WIDTH * p_GridX, EDIT_POSITION_Y_VALUE + EDIT_INTERVAL_HEIGHT * p_GridY,
                    EDIT_WIDTH_VALUE - EDIT_INTERVAL_WIDTH * p_GridX, EDIT_HEIGHT, m_hDlg, NULL, m_WndClass.hInstance, NULL);
                EnableWindow(hwndEdit, FALSE);
                SendMessage(hwndEdit, WM_SETFONT, (WPARAM)m_hFont, TRUE);
                if (p_GridY >= EDIT_HEIGHT_LIMIT) ShowWindow(hwndEdit, SW_HIDE);

                Var::DebugHandleEdits.push_back(make_pair(hwndEdit, Vector2(p_GridX, p_GridY)));
            }
            else
            {
                Var::DebugValue.push_back(p_JsonValue);
            }
        }
        else
        {
            if (!p_isUpdate)
            {
                HWND hwndEdit = CreateWindow("EDIT", p_JsonValue->asString().c_str(), WS_VISIBLE | WS_BORDER | WS_CHILD | WS_CLIPCHILDREN | ES_AUTOHSCROLL,
                    EDIT_POSITION_X_VALUE + EDIT_INTERVAL_WIDTH * p_GridX, EDIT_POSITION_Y_VALUE + EDIT_INTERVAL_HEIGHT * p_GridY,
                    EDIT_WIDTH_VALUE - EDIT_INTERVAL_WIDTH * p_GridX, EDIT_HEIGHT, m_hDlg, NULL, m_WndClass.hInstance, NULL);
                SendMessage(hwndEdit, WM_SETFONT, (WPARAM)m_hFont, TRUE);
                if (p_GridY >= EDIT_HEIGHT_LIMIT) ShowWindow(hwndEdit, SW_HIDE);

                Var::DebugHandleEdits.push_back(make_pair(hwndEdit, Vector2(p_GridX, p_GridY)));
            }
            else
            {
                Var::DebugValue.push_back(p_JsonValue);
            }
        }

        ++p_GridY;
    }
}

void DXFGame::ResetHandles()
{
    vector<pair<HWND, Vector2>>::iterator iter = Var::DebugHandleStatics.begin();
    while (iter != Var::DebugHandleStatics.end())
    {
        DestroyWindow(iter++->first);
    }
    Var::DebugHandleStatics.clear();

    iter = Var::DebugHandleEdits.begin();
    while (iter != Var::DebugHandleEdits.end())
    {
        DestroyWindow(iter++->first);
    }
    Var::DebugHandleEdits.clear();

    Var::DebugInspectorIndex = 0;
    Var::DebugInspectorMaxIndex = 0;
}

void DXFGame::UpdateHandles()
{
    m_HandleUpdateTerm += Time::deltaTime;
    if (m_HandleUpdateTerm < 0.1f)
    {
        return;
    }
    m_HandleUpdateTerm = 0;

    if (Var::DebugHandleStatics.size() > 0)
    {
        Var::DebugJson.clear();
        Var::DebugComponent->JsonSerialize(Var::DebugJson);

        Var::DebugValue.clear();
        int gridX = 0;
        int gridY = 0;

        CreateDebugHandles(&Var::DebugJson, gridX, gridY, false, true);

        HWND handle = GetFocus();

        bool deserialize = false;

        vector<pair<HWND, Vector2>>::iterator iter = Var::DebugHandleEdits.begin();
        for (int i = 0; iter != Var::DebugHandleEdits.end(); ++i)
        {
            TCHAR buffer[256];
            GetWindowText(iter->first, buffer, 255);

            if (iter->first == handle)
            {
                if (string(buffer) != Var::DebugValue[i]->asString())
                {
                    string str = string(buffer);

                    if (!str.empty())
                    {
                        switch (Var::DebugValue[i]->type())
                        {
                        case Json::ValueType::intValue:
                            try { *Var::DebugValue[i] = atoi(str.c_str()); }
                            catch (const std::invalid_argument& e) {}
                            break;
                        case Json::ValueType::booleanValue:
                            *Var::DebugValue[i] = (str == "true" || str == "1");
                            break;
                        case Json::ValueType::realValue:
                            try { *Var::DebugValue[i] = stod(str.c_str()); }
                            catch (const std::invalid_argument& e) { }
                            break;
                        case Json::ValueType::stringValue:
                            *Var::DebugValue[i] = str;
                            break;
                        }

                        deserialize = true;
                    }
                }
            }
            else
            {
                string str = Var::DebugValue[i]->asString();
                if (string(buffer) != str)
                {
                    SetWindowText(iter->first, str.c_str());
                }
            }

            ++iter;
        }

        if (deserialize)
        {
            Var::DebugComponent->JsonDeserialize(Var::DebugJson);
            string id = typeid(*Var::DebugComponent).name();
            if (id == "class Transform")
            {
                dynamic_cast<Transform*>(Var::DebugComponent)->WorldUpdate();
            }
            else if (id == "class RectTransform")
            {
                dynamic_cast<RectTransform*>(Var::DebugComponent)->ScreenUpdate();
            }
        }
    }
}