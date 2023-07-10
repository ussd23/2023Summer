//-----------------------------------------------------------------------------
// File: ComponentManager
//
// Desc: ������Ʈ�� string ������� ���� �� ��ȯ�ϴ� Ŭ����
//
//		[Functions]
//		- CreateInstance: Ŭ������� �ش� Ŭ������ ���丮 �Լ��� ����
//		- RegisterComponent: Ŭ���� ���
//      - CreateObject: ��ϵ� Ŭ������ ����
//-----------------------------------------------------------------------------

#pragma once
#include "StandardLibrary.h"
#include "Global.h"

class Component;

class ComponentManager
{
public:
    template<class T> static Component* CreateInstance(...);
    template<class T> static void RegisterComponent(const string&);
    static Component* CreateComponent(const string&, ...);
};

template<class T> Component* ComponentManager::CreateInstance(...)
{
    va_list args;
    va_start(args, nullptr);

    Base* instance = new T(args);

    va_end(args);

    return instance;
}

template<class T> void ComponentManager::RegisterComponent(const string& _class)
{
    g_ComponentMap[_class] = &CreateInstance<T>;
}