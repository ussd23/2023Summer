#include "ComponentHeader.h"
#include "Scripts.h"

void Sample3::ScriptRegister()
{
    ComponentRegist(CameraMove);
    ComponentRegist(TopText);
    ComponentRegist(ButtonTest);
    ComponentRegist(Minesweeper);
    ComponentRegist(Mine);
}