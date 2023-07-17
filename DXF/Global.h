//-----------------------------------------------------------------------------
// File: Global
//
// Desc: Global ���� �� ����
//
//		[Variables]
//		- g_Objects: ������Ʈ ��� (���� ������� push_back)
//		- g_ColliderObjects: Collider�� ����ϴ� ������Ʈ ���
//		- g_RootObject: Transform ���� �ֻ��� Parent ������Ʈ
//		- g_RootTransform: g_RootObject�� Transform ������Ʈ
//		- g_RootObject: RectTransform ���� �ֻ��� Parent ������Ʈ
//		- g_RootRectTransform: g_RootObject�� RectTransform ������Ʈ
//		- g_NewComponents: ���� ������� ������Ʈ (Start�� ����)
// 
//		- g_Frustum: ����ü �ø� ����� ���� Ŭ����
//      - g_CullingObjects: �������� ������Ʈ ��
//      - g_TransformRenderList: �������� Transform�� �̿��ϴ� ������Ʈ ����Ʈ
//      - g_RectTransformRenderList: �������� RectTransform�� �̿��ϴ� ������Ʈ
//                                   ����Ʈ
//
//		- g_mouse: ���콺�� �Է� ����
//		- g_mousepos: ���콺 �������� ��ǥ ��
//		- g_mouseraycast: ���콺 �������� ����� ��ǥ �� ������ Raycast ����
//		- g_key: Ű������ �Է� ���� (�Է� �������� ����)
//		- g_keyhold: Ű������ �Է� ���� (�Է� ���� ������ ��� �� �����Ӹ��� ����)
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