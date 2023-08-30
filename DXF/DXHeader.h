//-----------------------------------------------------------------------------
// File: DXHeader
//
// Desc: DirectX�� �ٽ� ��ɰ� DXF�� �߰� ���
//
//		[Variables]
//		- m_pD3D: Direct3D 9 ����̽� ������ ���� �׷��� API
//		- m_pd3dDevice: ������ ����̽�
//		- m_DefaultMaterial: ��Ƽ���� �⺻��
//		- m_DefaultTexture: �ؽ��� �⺻��
//		- m_pVB: ���ؽ� ����
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
//-----------------------------------------------------------------------------

#pragma once
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 )
#include <strsafe.h>
#include <time.h>
#pragma warning( default : 4996 )
#include "StandardLibrary.h"

using Vector2 = D3DXVECTOR2;
using Vector3 = D3DXVECTOR3;
using Vector4 = D3DXVECTOR4;
using Matrix = D3DXMATRIX;
using Matrix16 = D3DXMATRIXA16;
using Quaternion = D3DXQUATERNION;
using Plane = D3DXPLANE;

class DXFGame
{
protected:
	static Matrix16					m_ViewMatrix;
	static Matrix16					m_ProjMatrix;

public:
	static HWND						m_hWnd;
	static HWND						m_hDlg;
	static WNDCLASSEX				m_WndClass;
	static MSG						m_Msg;
	static string					m_Title;
	static Vector2					m_Resolution;
	static float					m_RenderDistance;
	static LPDIRECT3D9				m_pD3D;
	static LPDIRECT3DDEVICE9		m_pd3dDevice;
	static D3DMATERIAL9				m_DefaultMaterial;
	static IDirect3DBaseTexture9*	m_DefaultTexture;
	static LPDIRECT3DVERTEXBUFFER9	m_pVB;
	static LPD3DXSPRITE				m_pSprite;

public:
	static LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static INT_PTR WINAPI DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
	static HRESULT InitD3D(HINSTANCE hInst);

	static HRESULT SetupCamera();
	static HRESULT Render();
	static VOID Cleanup();

	static void ComponentRegister();
	static void Start();
	static void Update();
	static void Message();
};