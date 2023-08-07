//-----------------------------------------------------------------------------
// File: Global
//
// Desc: Global 설정 및 변수
//
//		[Class]
//		- Variables: Global 변수
//			- Objects: 오브젝트 목록 (생성 순서대로 push_back)
//			- ColliderObjects: Collider를 사용하는 오브젝트 목록
//			- RootObject: Transform 소유 최상위 Parent 오브젝트
//			- RootTransform: m_RootObject의 Transform 컴포넌트
//			- RootRectObject: RectTransform 소유 최상위 Parent 오브젝트
//			- RootRectTransform: m_RootRectObject의 RectTransform 컴포넌트
//			- NewComponents: 새로 만들어진 컴포넌트 (Awake를 위함)
//			- WaitComponents: Awake 된 컴포넌트 (Start를 위함)
// 
//			- Frustum: 절두체 컬링 사용을 위한 클래스
//			- CullingObjects: 렌더링한 오브젝트 수
//			- TransformRenderList: 렌더링할 Transform 오브젝트 리스트
//			- RectTransformRenderList: 렌더링할 RectTransform 오브젝트 리스트
// 
//		- Input: Input 변수
//			- Mouse: 마우스의 입력 버퍼
//			- MousePosition: 마우스 포인터의 좌표 값
//			- MouseRaycast: 마우스 포인터의 월드상 좌표 및 직선의 Raycast 정보
//			- Key: 키보드의 입력 버퍼 (입력 시점에만 적용)
//			- KeyHold: 키보드의 입력 버퍼 (입력 중인 상태인 경우 매 프레임마다 적용)
// 
//			- InputBufferReset: 입력 버퍼 초기화 작업 실행
// 
//		- Time: Time 변수
//			- deltaTime: 이전 프레임과 현재 프레임 간의 시간 차이
//			- framePerSec: 초당 프레임 업데이트 수
//			- avgFrame: 애플리케이션 실행 이후 평균 초당 프레임
//			- TimeUpdate: deltaTime 연산
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

#define SCREENSIZEX 1600
#define SCREENSIZEY 900
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

typedef class Variables
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
} Global, Var;

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