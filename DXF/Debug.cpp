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
}

void DXFGame::DebugCheck()
{
	if (m_DebugUpdate)
	{
		m_DebugUpdateTerm += Time::deltaTime;
		DebugUpdate();
	}
}