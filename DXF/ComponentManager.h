//-----------------------------------------------------------------------------
// File: ComponentManager
//
// Desc: 컴포넌트를 string 기반으로 생성 및 반환하는 클래스
//
//		[Functions]
//		- CreateInstance: 클래스명과 해당 클래스의 팩토리 함수를 매핑
//		- RegisterComponent: 클래스 등록
//      - CreateObject: 등록된 클래스를 생성
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