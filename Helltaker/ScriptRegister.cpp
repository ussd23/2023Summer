#include "ComponentHeader.h"
#include "Scripts.h"

void Helltaker::ScriptRegister()
{
    ComponentRegist(CameraMove);
    ComponentRegist(ObjectMove);
    ComponentRegist(PlayerMove);
    ComponentRegist(TopText);
}