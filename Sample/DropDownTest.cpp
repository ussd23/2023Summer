#include "Scripts.h"

void DropDownTest::Start()
{
    m_DropDown = GetComponentFromObject(gameObject, DropDown);

    if (m_DropDown == nullptr) return;

    // DropDownOption1
    GameObject* childObject = new DropDownOptionObject("DropDownOption1", "¸¼Àº °íµñ", 28, "Option1");
    RectTransform* recttransform = GetComponentFromObject(m_DropDown->gameObject, RectTransform);
    RectTransform* childrecttransform = GetComponentFromObject(childObject, RectTransform);
    recttransform->AddChild(childrecttransform);

    m_DropDown->m_Options.push_back(childObject);

    // DropDownOption2
    childObject = new DropDownOptionObject("DropDownOption2", "¸¼Àº °íµñ", 28, "Option2");
    childrecttransform = GetComponentFromObject(childObject, RectTransform);
    recttransform->AddChild(childrecttransform);

    m_DropDown->m_Options.push_back(childObject);

    m_DropDown->SetChildRect();
}

