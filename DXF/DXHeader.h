//-----------------------------------------------------------------------------
// File: DXHeader
//
// Desc: DirectX의 핵심 기능과 DXF의 추가 기능
//
//		[Variables]
//		- m_pD3D: Direct3D 9 디바이스 생성을 위한 그래픽 API
//		- m_pd3dDevice: 렌더링 디바이스
//		- m_DefaultMaterial: 머티리얼 기본값
//		- m_DefaultTexture: 텍스쳐 기본값
//		- m_pVB: 버텍스 버퍼
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