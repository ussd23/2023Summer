#include "ComponentHeader.h"
#include "Scripts.h"

void ScriptRegister()
{
    ComponentManager::RegisterComponent<CameraMove>("CameraMove");
    ComponentManager::RegisterComponent<ObjectMove>("ObjectMove");
    ComponentManager::RegisterComponent<PlayerMove>("PlayerMove");
    ComponentManager::RegisterComponent<TopText>("TopText");
}