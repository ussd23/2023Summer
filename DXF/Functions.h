//-----------------------------------------------------------------------------
// File: Functions
//
// Desc: DXF 내에서 사용 가능한 다양한 함수를 포함하고 있음.
//
//      [Functions]
//      - Lerp: 선형 보간 (두 값 사이의 중간값을 반환)
//      - Inner: 2차원 범위 안에 해당 좌표가 속해있는 지의 여부 반환
//      - WorldToScreen: 월드상 오브젝트의 위치를 화면상 좌표로 변환
//      - GetDistanceSquare: 두 좌표 사이의 거리의 제곱 반환
//
//      [Macro]
//      - AddComponentToObject: 오브젝트에 컴포넌트 추가
//      - GetComponentFromObject: 오브젝트에서 특정 컴포넌트 반환 (해당 오브젝트
//                                또는 컴포넌트가 없을 경우 nullptr 반환)
//      - SetInputBuffer: InputBuffer 세팅 (MsgProc에서만 사용하길 권장)
//      - GetInputBuffer: InputBuffer의 탐색을 원하는 key의 값을 반환 (해당되는
//                        key 값이 없을 경우 false 반환)
//-----------------------------------------------------------------------------

#pragma once
#include "DXHeader.h"
#include "StandardLibrary.h"

class GameObject;
class Transform;

namespace Functions
{;
template <typename T> T Lerp(T p_Start, T p_End, float p_LerpT);

bool Inner(const RECT& p_Rect, const Vector2& p_Position);
bool Inner(const RECT& p_Rect1, const RECT& p_Rect2);
Vector2 WorldToScreen(Transform* p_Transform);
float GetDistanceSquare(const Vector2& p_Point1, const Vector2& p_Point2);
float GetDistanceSquare(const Vector3& p_Point1, const Vector3& p_Point2);
float GetDistanceSquare(const Vector4& p_Point1, const Vector4& p_Point2);

Vector3 SLerp(const Vector3* p_Origin, const Vector3* p_Destination, float p_LerpT);

Quaternion EulerToQuaternion(Vector3 p_Euler);
Vector3 QuaternionToEuler(Quaternion p_Quaternion);

Vector2 VectorRotate(Quaternion p_Quaternion, Vector2 p_Vector);
Vector3 VectorRotate(Quaternion p_Quaternion, Vector3 p_Vector);

void CreateJsonFile(string p_Path, Json::Value p_JsonValue);
}

template <typename T> T Functions::Lerp(T p_Start, T p_End, float p_LerpT)
{
    if (p_LerpT > 1) p_LerpT = 1;
    return p_Start + p_LerpT * (p_End - p_Start);
}

#define AddComponentToObject(object, component) object->AddComponent(component)
#define GetComponentFromObject(object, type) GameObject::Exists(object) ? dynamic_cast<type*>(object->GetComponent(#type)) : nullptr
#define ComponentRegist(type) ComponentManager::RegisterComponent<type>(typeid(type).name())

#define SetInputBuffer(object, type, value) if (Input::object.find(type) == Input::object.end()) Input::object.insert(make_pair(type, value));\
        else Input::object[type] = value
#define GetInputBuffer(object, type) (Input::object.find(type) == Input::object.end()) ? false : Input::object[type]
