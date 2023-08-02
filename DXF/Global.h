//-----------------------------------------------------------------------------
// File: Global
//
// Desc: Global ���� �� ����
//
//		[Class]
//		- Variables: Global ����
//			- m_Objects: ������Ʈ ��� (���� ������� push_back)
//			- m_ColliderObjects: Collider�� ����ϴ� ������Ʈ ���
//			- m_RootObject: Transform ���� �ֻ��� Parent ������Ʈ
//			- m_RootTransform: m_RootObject�� Transform ������Ʈ
//			- m_RootRectObject: RectTransform ���� �ֻ��� Parent ������Ʈ
//			- m_RootRectTransform: m_RootRectObject�� RectTransform ������Ʈ
//			- m_NewComponents: ���� ������� ������Ʈ (Start�� ����)
// 
//			- m_Frustum: ����ü �ø� ����� ���� Ŭ����
//			- m_CullingObjects: �������� ������Ʈ ��
//			- m_TransformRenderList: �������� Transform ������Ʈ ����Ʈ
//			- m_RectTransformRenderList: �������� RectTransform ������Ʈ ����Ʈ
// 
//		- Input: Input ����
//			- m_Mouse: ���콺�� �Է� ����
//			- m_MousePosition: ���콺 �������� ��ǥ ��
//			- m_MouseRaycast: ���콺 �������� ����� ��ǥ �� ������ Raycast ����
//			- m_Key: Ű������ �Է� ���� (�Է� �������� ����)
//			- m_KeyHold: Ű������ �Է� ���� (�Է� ���� ������ ��� �� �����Ӹ��� ����)
//			- InputBufferReset: �Է� ���� �ʱ�ȭ �۾� ����
// 
//		- Time: Time ����
//			- deltaTime: ���� �����Ӱ� ���� ������ ���� �ð� ����
//			- framePerSec: �ʴ� ������ ������Ʈ ��
//			- avgFrame: ���ø����̼� ���� ���� ��� �ʴ� ������
//			- TimeUpdate: deltaTime ����
//-----------------------------------------------------------------------------

#pragma once
#include "StandardLibrary.h"
#include "DXHeader.h"
#include "Raycast.h"
#include "Component.h"
#include "SPTR.h"
#include "GetI.h"

class GameObject;
class Transform;
class RectTransform;
class Frustum;
class Renderer;

#define SCREENSIZEX 1600
#define SCREENSIZEY 900
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

class Variables
{
public:
	static list<SPTR<GameObject>>	Objects;
	static list<GameObject*>		ColliderObjects;
	static GameObject*				RootObject;
	static Transform*				RootTransform;
	static GameObject*				RootRectObject;
	static RectTransform*			RootRectTransform;
	static vector<Component*>		NewComponents;

	static RECT						ScreenRect;
	static Frustum*					Frustum;
	static int						CullingObjects;
	static vector<Renderer*>		TransformRenderList;
	static vector<Renderer*>		RectTransformRenderList;
};

using Var = Variables;

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

class Input
{
public:
	static map<MouseInput, bool>	Mouse;
	static Vector2					MousePosition;
	static Raycast					MouseRaycast;
	static map<WPARAM, bool>		Key;
	static map<WPARAM, bool>		KeyHold;

public:
	static void InputBufferReset();
};

class Time
{
protected:
	static UINT					pastTime;
	static int					sec;
	static int					frames;
	static int					passedFrames;
	static int					passedTime;

public:
	static FLOAT				deltaTime;
	static int					framePerSec;
	static float				avgFrame;

public:
	static void TimeUpdate();
};