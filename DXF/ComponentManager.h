//-----------------------------------------------------------------------------
// File: ComponentManager
//
// Desc: 
//
//		[Functions]
//		- CreateInstance: 
//		- RegisterComponent: 
//      - CreateObject: 
//-----------------------------------------------------------------------------

#pragma once
#include "StandardLibrary.h"

class Component;
typedef Component* (*FactoryFunction)();

class ComponentManager
{
public:
    static map<string, FactoryFunction> m_ComponentMap;

public:
    template<class T> static Component* CreateInstance();
    template<class T> static void RegisterComponent(const string&);
    static Component* CreateComponent(const string&);
};

template<class T> Component* ComponentManager::CreateInstance()
{
    Component* instance = new T();
    return instance;
}

template<class T> void ComponentManager::RegisterComponent(const string& _class)
{
    m_ComponentMap[_class] = &CreateInstance<T>;
}