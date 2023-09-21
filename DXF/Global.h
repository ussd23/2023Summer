//-----------------------------------------------------------------------------
// File: Global
//
// Desc: Global ���� �� ����
//
//		[Class]
//		- Variables: Global ����
//			- Objects: ������Ʈ ��� (���� ������� push_back)
//			- ColliderObjects: Collider�� ����ϴ� ������Ʈ ���
//			- RootObject: Transform ���� �ֻ��� Parent ������Ʈ
//			- RootTransform: m_RootObject�� Transform ������Ʈ
//			- RootRectObject: RectTransform ���� �ֻ��� Parent ������Ʈ
//			- RootRectTransform: m_RootRectObject�� RectTransform ������Ʈ
//			- NewComponents: ���� ������� ������Ʈ (Awake�� ����)
//			- WaitComponents: Awake �� ������Ʈ (Start�� ����)
// 
//			- Frustum: ����ü �ø� ����� ���� Ŭ����
//			- CullingObjects: �������� ������Ʈ ��
//			- TransformRenderList: �������� Transform ������Ʈ ����Ʈ
//			- RectTransformRenderList: �������� RectTransform ������Ʈ ����Ʈ
// 
//		- Input: Input ����
//			- Mouse: ���콺�� �Է� ����
//			- MousePosition: ���콺 �������� ��ǥ ��
//			- MouseRaycast: ���콺 �������� ����� ��ǥ �� ������ Raycast ����
//			- Key: Ű������ �Է� ���� (�Է� �������� ����)
//			- KeyHold: Ű������ �Է� ���� (�Է� ���� ������ ��� �� �����Ӹ��� ����)
// 
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
class MouseFunction;
class Renderer;
class Frustum;

typedef class Var
{
public:
	static list<SPTR<GameObject>>	Objects;
	static list<GameObject*>		ColliderObjects;
	static GameObject*				RootObject;
	static Transform*				RootTransform;
	static GameObject*				RootRectObject;
	static RectTransform*			RootRectTransform;
	static vector<Component*>		NewComponents;
	static list<Component*>			WaitComponents;

	static RECT						ScreenRect;
	static Frustum*					Frustum;
	static int						CullingObjects;
	static vector<Renderer*>		TransformRenderList;
	static vector<Renderer*>		RectTransformRenderList;
	static vector<Renderer*>		StencilMaskRenderList;
	static vector<Renderer*>		StenciledObjectRenderList;
} Global;

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
	static void InputBufferReset(bool p_Option);
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


class DebugModeCls
{
public:
	static bool ISStencil;
	static bool ISStencil2;
};

