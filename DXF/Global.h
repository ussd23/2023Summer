//-----------------------------------------------------------------------------
// File: Global
//
// Desc: Global 설정 및 변수
//
//		[Variables]
//		- g_Objects: 오브젝트 목록 (생성 순서대로 push_back)
//		- g_ColliderObjects: Collider를 사용하는 오브젝트 목록
//		- g_RootObject: Transform 소유 최상위 Parent 오브젝트
//		- g_RootTransform: g_RootObject의 Transform 컴포넌트
//		- g_RootObject: RectTransform 소유 최상위 Parent 오브젝트
//		- g_RootRectTransform: g_RootObject의 RectTransform 컴포넌트
//		- g_NewComponents: 새로 만들어진 컴포넌트 (Start를 위함)
// 
//		- g_Frustum: 절두체 컬링 사용을 위한 클래스
//      - g_CullingObjects: 렌더링한 오브젝트 수
//      - g_TransformRenderList: 렌더링할 Transform을 이용하는 오브젝트 리스트
//      - g_RectTransformRenderList: 렌더링할 RectTransform을 이용하는 오브젝트
//                                   리스트
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
class Frustum;
class Renderer;
template<typename T> class SPTR;

#define SCREENSIZEX 1600
#define SCREENSIZEY 900
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

#ifdef WINMAIN
list<SPTR<GameObject>>		    g_Objects;
list<GameObject*>		        g_ColliderObjects;
GameObject*						g_RootObject;
Transform*						g_RootTransform;
GameObject*						g_RootRectObject;
RectTransform*					g_RootRectTransform;
vector<Component*>              g_NewComponents;

RECT                            g_ScreenRect;
Frustum*                        g_Frustum;
int                             g_CullingObjects;
vector<Renderer*>               g_TransformRenderList;
vector<Renderer*>               g_RectTransformRenderList;
#else
extern list<SPTR<GameObject>>	g_Objects;
extern list<GameObject*>	    g_ColliderObjects;
extern GameObject*				g_RootObject;
extern Transform*				g_RootTransform;
extern GameObject*				g_RootRectObject;
extern RectTransform*			g_RootRectTransform;
extern vector<Component*>       g_NewComponents;

extern RECT                     g_ScreenRect;
extern Frustum*                 g_Frustum;
extern int                      g_CullingObjects;
extern vector<Renderer*>        g_TransformRenderList;
extern vector<Renderer*>        g_RectTransformRenderList;
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
protected:
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