//-----------------------------------------------------------------------------
// File: DXHeader
//
// Desc: DirectX�� �ٽ� ��ɰ� DXF�� �߰� ���
//
//		[Variables]
//		- g_pD3D: Direct3D 9 ����̽� ������ ���� �׷��� API
//		- g_pd3dDevice: ������ ����̽�
//		- g_defaultMaterial: ��Ƽ���� �⺻��
//		- g_defaultTexture: �ؽ��� �⺻��
//		- g_pVB: ���ؽ� ����
//		- deltaTime: ���� �����Ӱ� ���� ������ ���� �ð� ����
//		- framePerSec: �ʴ� ������ ������Ʈ ��
//		- avgFrame: ���ø����̼� ���� ���� ��� �ʴ� ������
//
//		[Functions]
//		- MsgProc: �޽��� ���� ���� �Է� ������ ���� �����ϰų� ���α׷� ����
//		- InitD3D: Direct3D 9 �� ����̽� ���� ���� �ʱ� �۾� ����
//		- SetupCamera: Main ī�޶��� Transform ���� �޾ƿ� ī�޶� ����
//		- Render: Renderer�� �ִ� ������Ʈ�� Render �۾� �ϰ� ����
//				  (Transform�� Parent/Child ���� ������ ����)
//		- Cleanup: ������ �ʱ�ȭ�� ��� ��ü�� ����
//		- Start: ������Ʈ ������ ��� ������Ʈ�� Start �۾� �ϰ� ����
//				 (������Ʈ�� ������ ������� ����)
//		- Update: ������Ʈ ������ ��� ������Ʈ�� Update �۾� �ϰ� ����
//				 (Transform�� Parent/Child ���� ������ ����)
//		- InputBufferReset: �Է� ���� �ʱ�ȭ �۾� ����
//		- TimeUpdate: deltaTime ����
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