#include "ComponentHeader.h"
#include "Scripts.h"

void Sample3::ScriptRegister() {
    ComponentRegist(CameraMove);
    ComponentRegist(TopText);
    ComponentRegist(ResetButton);
    ComponentRegist(ResetButtonText);
    ComponentRegist(Minesweeper);
    ComponentRegist(Mine);
}