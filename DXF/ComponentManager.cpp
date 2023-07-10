#include "ComponentManager.h"

Component* ComponentManager::CreateComponent(const string& _class, ...)
{
    if (g_ComponentMap.find(_class) != g_ComponentMap.end())
    {
        FactoryFunction factory = g_ComponentMap[_class];
        
        va_list args;
        va_start(args, _class);

        Component* instance = factory(args);

        va_end(args);

        return instance;
    }
    return nullptr;
}
