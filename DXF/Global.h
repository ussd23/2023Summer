//-----------------------------------------------------------------------------
// File: Global
//
// Desc: Global 설정 및 변수
//
//		[Variables]
//		- g_Objects: 오브젝트 목록 (생성 순서대로 push_back)
//		- g_RootObject: Transform 소유 최상위 Parent 오브젝트
//		- g_RootTransform: g_RootObject의 Transform 컴포넌트
//		- g_RootObject: RectTransform 소유 최상위 Parent 오브젝트
//		- g_RootRectTransform: g_RootObject의 RectTransform 컴포넌트
//
//		- g_mouse: 마우스의 입력 버퍼
//		- g_mousepos: 마우스 포인터의 좌표 값
//		- g_mouseraycast: 마우스 포인터의 월드상 좌표 및 직선의 Raycast 정보
//		- g_key: 키보드의 입력 버퍼 (입력 시점에만 적용)
//		- g_keyhold: 키보드의 입력 버퍼 (입력 중인 상태인 경우 매 프레임마다 적용)
//-----------------------------------------------------------------------------

#pragma once
#include "StandardLibrary.h"
#include "DXHeader.h"
#include "Raycast.h"
#include "Component.h"

class GameObject;
class Transform;
class RectTransform;
template<typename T> class SPTR;

#define SCREENSIZEX 1600
#define SCREENSIZEY 900
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

#ifdef WINMAIN
list<SPTR<GameObject>>		    g_Objects;
GameObject*						g_RootObject;
Transform*						g_RootTransform;
GameObject*						g_RootRectObject;
RectTransform*					g_RootRectTransform;
vector<Component*>              g_NewComponents;
#else
extern list<SPTR<GameObject>>	g_Objects;
extern GameObject*				g_RootObject;
extern Transform*				g_RootTransform;
extern GameObject*				g_RootRectObject;
extern RectTransform*			g_RootRectTransform;
extern vector<Component*>       g_NewComponents;
#endif

enum MouseInput
{
	LBUTTONHOLD,
	RBUTTONHOLD,
	MBUTTONHOLD,

	LBUTTONDOWN,
	RBUTTONDOWN,
	MBUTTONDOWN,

	LBUTTONUP,
	RBUTTONUP,
	MBUTTONUP,

	WHEELUP,
	WHEELDOWN,

	END,
};

#ifdef WINMAIN
map<MouseInput, bool>			g_mouse;
Vector2							g_mousepos;
Raycast							g_mouseraycast;
map<WPARAM, bool>				g_key;
map<WPARAM, bool>				g_keyhold;
#else
extern map<MouseInput, bool>	g_mouse;
extern Vector2					g_mousepos;
extern Raycast					g_mouseraycast;
extern map<WPARAM, bool>		g_key;
extern map<WPARAM, bool>		g_keyhold;
#endif

template<typename T> class SPTR
{
private:
    T* ptr;

public:
    static map<T*, int>         ReferenceCounts;

public:
    SPTR() : SPTR(nullptr) {}

    SPTR(T* _ptr)
    {
        ptr = _ptr;
        RefUp();
    }
    
    SPTR(const SPTR& other)
    {
        ptr = other.ptr;
        RefUp();
    }

    virtual ~SPTR()
    {
        RefDown();
    }

    void operator=(T* _ptr)
    {
        if (ptr != _ptr)
        {
            RefDown();
            ptr = _ptr;
            RefUp();
        }
    }

    bool operator==(T* _ptr)
    {
        if (ptr == _ptr) return true;
        else return false;
    }

    bool operator==(const SPTR& other)
    {
        if (ptr == other->ptr) return true;
        else return false;
    }

    bool operator!=(T* _ptr)
    {
        if (ptr != _ptr) return true;
        else return false;
    }

    bool operator!=(const SPTR& other)
    {
        if (ptr != other->ptr) return true;
        else return false;
    }

    T* operator->()
    {
        return ptr;
    }

    T* operator()()
    {
        return ptr;
    }

    void RefUp()
    {
        if (ptr == nullptr) return;

        if (ReferenceCounts.find(ptr) == ReferenceCounts.end())
        {
            ReferenceCounts.insert(make_pair(ptr, 1));
        }
        else
        {
            ReferenceCounts[ptr] += 1;
        }
    }

    void RefDown()
    {
        if (ptr == nullptr) return;

        if (ReferenceCounts.find(ptr) != ReferenceCounts.end())
        {
            ReferenceCounts[ptr] -= 1;
            if (ReferenceCounts[ptr] == 0)
            {
                ReferenceCounts.erase(ReferenceCounts.find(ptr));
                delete ptr;
            }
        }
    }
};

template<typename T> map<T*, int> SPTR<T>::ReferenceCounts;