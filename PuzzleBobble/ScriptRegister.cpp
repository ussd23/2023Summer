#include "ComponentHeader.h"
#include "Scripts.h"

void PuzzleBobble::ScriptRegister()
{
    ComponentRegist(Bubble);
    ComponentRegist(BubbleManager);
    ComponentRegist(Controll);
}