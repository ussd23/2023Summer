//-----------------------------------------------------------------------------
// File: Functions
//
// Desc: DXF 내에서 사용 가능한 다양한 함수를 포함하고 있음.
//
//      [Functions]
//      - Lerp: 선형 보간 (두 값 사이의 중간값을 반환)
//      - Inner: 2차원 범위 안에 해당 좌표가 속해있는 지의 여부 반환
//      - WorldToScreen: 월드상 오브젝트의 위치를 화면상 좌표로 변환
//      - GetDistance: 두 좌표 사이의 거리 반환
//
//      [Macro]
//      - AddObjectToScene: 오브젝트를 처음 생성시 사용
//      - AddComponentToObject: 오브젝트에 컴포넌트 추가
//      - GetComponentFromObject: 오브젝트에서 특정 컴포넌트 반환 (해당 오브젝트
//                                또는 컴포넌트가 없을 경우 nullptr 반환)
//      - SetInputBuffer: InputBuffer 세팅 (MsgProc에서만 사용하길 권장)
//      - GetInputBuffer: InputBuffer의 탐색을 원하는 key의 값을 반환 (해당되는
//                        key 값이 없을 경우 false 반환)
//-----------------------------------------------------------------------------

#pragma once
#include "DXHeader.h"

class GameObject;
class Transform;

namespace Functions
{;
template <typename T> T Lerp(T, T, float);
//float Lerp(float, float, float);

bool Inner(RECT, D3DXVECTOR2);
D3DXVECTOR2 WorldToScreen(Transform*);
float GetDistance(D3DXVECTOR3, D3DXVECTOR3);

D3DXVECTOR3 SLerp(const D3DXVECTOR3*, const D3DXVECTOR3*, float);
D3DXVECTOR3 D3DXQuaternionToRotation(D3DXQUATERNION);
}

template <typename T> T Functions::Lerp(T startValue, T endValue, float t)
{
    return startValue + t * (endValue - startValue);
}

#define AddObjectToScene(object, parent, transform) g_Objects.push_back(object);\
        parent->AddChild(transform);
#define AddComponentToObject(object, component) object->AddComponent(component)
#define GetComponentFromObject(object, type) GameObject::Exists(object) ? dynamic_cast<type*>(object->GetComponent(#type)) : nullptr

#define SetInputBuffer(object, type, value) if (object.find(type) == object.end()) object.insert(make_pair(type, value));\
        else object[type] = value
#define GetInputBuffer(object, type) (object.find(type) == object.end()) ? false : object[type]
