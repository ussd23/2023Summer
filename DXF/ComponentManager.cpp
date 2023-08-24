#include "ComponentManager.h"

map<string, FactoryFunction> ComponentManager::m_ComponentMap;

Component* ComponentManager::CreateComponent(const string& _class)
{
    if (m_ComponentMap.find(_class) != m_ComponentMap.end())
    {
        FactoryFunction factory = m_ComponentMap[_class];

        Component* instance = factory();

        return instance;
    }
    return nullptr;
}