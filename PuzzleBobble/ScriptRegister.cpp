#include "ComponentHeader.h"
#include "Scripts.h"

void PuzzleBobble::ScriptRegister()
{
    ComponentRegist(CameraMove);
    ComponentRegist(ObjectMove);
    ComponentRegist(PlayerMove);
    ComponentRegist(TopText);
    ComponentRegist(BtnText);
    ComponentRegist(ButtonTest);
}