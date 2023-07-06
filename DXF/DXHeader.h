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
//		- Cleanup: ������ �ʱ�ȭ�� ��� ��ü�� ����
//		- SetupCamera: Main ī�޶��� Transform ���� �޾ƿ� ī�޶� ����
//		- Render: Renderer�� �ִ� ������Ʈ�� Render �۾� �ϰ� ����
//				  (Transform�� Parent/Child ���� ������ ����)
//		- Start: ������Ʈ ������ ��� ������Ʈ�� Start �۾� �ϰ� ����
//				 (������Ʈ�� ������ ������� ����)
//		- Update: ������Ʈ ������ ��� ������Ʈ�� Update �۾� �ϰ� ����
//				 (Transform�� Parent/Child ���� ������ ����)
//		- InitObject: ���ø����̼��� ���� ���� �ʱ� ������Ʈ ���� �� ���� �� ����
//		- TimeUpdate: deltaTime ����
//		- InputBufferReset: �Է� ���� �ʱ�ȭ �۾� ����
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

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HRESULT InitD3D(HWND hWnd);

VOID Cleanup();
HRESULT SetupCamera();
HRESULT Render();

namespace Time
{;
#ifdef WINMAIN
FLOAT							deltaTime;
int								framePerSec;
float							avgFrame;
#else
extern FLOAT					deltaTime;
extern int						framePerSec;
extern float					avgFrame;
#endif
}

namespace Game
{;
void Start();
void Update();
void InitObject();
void TimeUpdate();
void InputBufferReset();
}

template<typename T> class SPTR
{
private:
    T* ptr;

public:
    SPTR() : SPTR(nullptr) {}

    SPTR(T* _ptr)
    {
        ptr = _ptr;
    }

    void operator=(T* _ptr)
    {
        if (ptr != _ptr)
        {
            delete ptr;
            ptr = _ptr;
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
};