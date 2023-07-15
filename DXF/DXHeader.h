//-----------------------------------------------------------------------------
// File: DXHeader
//
// Desc: DirectX의 핵심 기능과 DXF의 추가 기능
//
//		[Variables]
//		- g_pD3D: Direct3D 9 디바이스 생성을 위한 그래픽 API
//		- g_pd3dDevice: 렌더링 디바이스
//		- g_defaultMaterial: 머티리얼 기본값
//		- g_defaultTexture: 텍스쳐 기본값
//		- g_pVB: 버텍스 버퍼
//		- deltaTime: 이전 프레임과 현재 프레임 간의 시간 차이
//		- framePerSec: 초당 프레임 업데이트 수
//		- avgFrame: 애플리케이션 실행 이후 평균 초당 프레임
//
//		[Functions]
//		- MsgProc: 메시지 값에 따라 입력 버퍼의 값을 세팅하거나 프로그램 종료
//		- InitD3D: Direct3D 9 및 디바이스 생성 등의 초기 작업 실행
//		- SetupCamera: Main 카메라의 Transform 등을 받아와 카메라 설정
//		- Render: Renderer가 있는 오브젝트의 Render 작업 일괄 실행
//				  (Transform의 Parent/Child 구조 순으로 실행)
//		- Cleanup: 이전에 초기화된 모든 개체를 해제
//		- Start: 오브젝트 소유의 모든 컴포넌트의 Start 작업 일괄 실행
//				 (오브젝트가 생성된 순서대로 실행)
//		- Update: 오브젝트 소유의 모든 컴포넌트의 Update 작업 일괄 실행
//				 (Transform의 Parent/Child 구조 순으로 실행)
//		- InputBufferReset: 입력 버퍼 초기화 작업 실행
//		- TimeUpdate: deltaTime 연산
//-----------------------------------------------------------------------------

#pragma once
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 )
#include <strsafe.h>
#include <time.h>
#pragma warning( default : 4996 )

using Vector2 = D3DXVECTOR2;
using Vector3 = D3DXVECTOR3;
using Vector4 = D3DXVECTOR4;
using Matrix = D3DXMATRIX;
using Matrix16 = D3DXMATRIXA16;
using Quaternion = D3DXQUATERNION;
using Plane = D3DXPLANE;

#ifdef WINMAIN
LPDIRECT3D9						g_pD3D = NULL;
LPDIRECT3DDEVICE9				g_pd3dDevice = NULL;
D3DMATERIAL9					g_defaultMaterial;
IDirect3DBaseTexture9*			g_defaultTexture;
LPDIRECT3DVERTEXBUFFER9			g_pVB = NULL;
LPD3DXSPRITE					g_pSprite = NULL;
#else
extern LPDIRECT3D9				g_pD3D;
extern LPDIRECT3DDEVICE9		g_pd3dDevice;
extern D3DMATERIAL9				g_defaultMaterial;
extern IDirect3DBaseTexture9*	g_defaultTexture;
extern LPDIRECT3DVERTEXBUFFER9	g_pVB;
extern LPD3DXSPRITE				g_pSprite;
#endif

class DXFGame
{
private:
	static Matrix16 viewMatrix;
	static Matrix16 projMatrix;

public:
	static LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static HRESULT InitD3D(HWND hWnd);

	static HRESULT SetupCamera();
	static HRESULT Render();
	static VOID Cleanup();

	static void Start();
	static void Update();
	static void InputBufferReset();
};

class Time
{
private:
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