#include "ComponentHeader.h"
#include "Scripts.h"

void Sample_UI::ScriptRegister()
{
    ComponentRegist(CameraMove);
    ComponentRegist(ObjectMove);
    ComponentRegist(PlayerMove);
    ComponentRegist(TopText);
    ComponentRegist(BtnText);
    ComponentRegist(ButtonTest);
    ComponentRegist(DropDownTest);
    ComponentRegist(DropDownText);
}