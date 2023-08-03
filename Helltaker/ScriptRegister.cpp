#include "ComponentHeader.h"
#include "Scripts.h"

void Helltaker::ScriptRegister()
{
    ComponentManager::RegisterComponent<CameraMove>(typeid(CameraMove).name());
    ComponentManager::RegisterComponent<ObjectMove>(typeid(ObjectMove).name());
    ComponentManager::RegisterComponent<PlayerMove>(typeid(PlayerMove).name());
    ComponentManager::RegisterComponent<TopText>(typeid(TopText).name());
}