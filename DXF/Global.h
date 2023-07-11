//-----------------------------------------------------------------------------
// File: Global
//
// Desc: Global ���� �� ����
//
//		[Variables]
//		- g_Objects: ������Ʈ ��� (���� ������� push_back)
//		- g_RootObject: Transform ���� �ֻ��� Parent ������Ʈ
//		- g_RootTransform: g_RootObject�� Transform ������Ʈ
//		- g_RootObject: RectTransform ���� �ֻ��� Parent ������Ʈ
//		- g_RootRectTransform: g_RootObject�� RectTransform ������Ʈ
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

class GameObject;
class Transform;
class RectTransform;

#define SCREENSIZEX 1600
#define SCREENSIZEY 900
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)


#ifdef WINMAIN
vector<SPTR<GameObject>>		g_Objects;
GameObject*						g_RootObject;
Transform*						g_RootTransform;
GameObject*						g_RootRectObject;
RectTransform*					g_RootRectTransform;
#else
extern vector<SPTR<GameObject>>	g_Objects;
extern GameObject*				g_RootObject;
extern Transform*				g_RootTransform;
extern GameObject*				g_RootRectObject;
extern RectTransform*			g_RootRectTransform;
#endif

enum MouseInput
{
	LBUTTONHOLD,
	RBUTTONHOLD,
	MBUTTONHOLD,

	LBUTTONCLK,
	RBUTTONCLK,
	MBUTTONCLK,

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