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
#include "StandardLibrary.h"

class GameObject;
class Transform;

namespace Functions
{;
template <typename T> T Lerp(T p_Start, T p_End, float p_LerpT);

bool Inner(const RECT& p_Rect, const Vector2& p_Position);
bool Inner(const RECT& p_Rect1, const RECT& p_Rect2);
Vector2 WorldToScreen(Transform* p_Transform);
float GetDistanceSquare(const Vector2&, const Vector2&);
float GetDistanceSquare(const Vector3&, const Vector3&);
float GetDistanceSquare(const Vector4&, const Vector4&);

Vector3 SLerp(const Vector3* p_Origin, const Vector3* p_Destination, float p_LerpT);

Quaternion EulerToQuaternion(Vector3 p_Euler);
Vector3 QuaternionToEuler(Quaternion p_Quaternion);

template <typename T> void Serialize(const T& data, ofstream& outFile);
template <typename T> void Deserialize(T& data, ifstream& inFile);
}

template <typename T> T Functions::Lerp(T p_Start, T p_End, float p_LerpT)
{
    return p_Start + p_LerpT * (p_End - p_Start);
}

template <typename T> void Functions::Serialize(const T& data, ofstream& outFile)
{
    outFile.write(reinterpret_cast<const char*>(&data), sizeof(T));
}

template <typename T> void Functions::Deserialize(T& data, ifstream& inFile)
{
    inFile.read(reinterpret_cast<char*>(&data), sizeof(T));
}

#define AddObjectToScene(object, parent, transform) g_Objects.push_back(object);\
        parent->AddChild(transform);
#define AddComponentToObject(object, component) object->AddComponent(component)
#define GetComponentFromObject(object, type) GameObject::Exists(object) ? dynamic_cast<type*>(object->GetComponent(#type)) : nullptr

#define SetInputBuffer(object, type, value) if (object.find(type) == object.end()) object.insert(make_pair(type, value));\
        else object[type] = value
#define GetInputBuffer(object, type) (object.find(type) == object.end()) ? false : object[type]

#define SerializeFunctions(type) string Serialize() override\
{\
    string buffer(reinterpret_cast<const char*>(this), sizeof(type));\
    return buffer;\
}\
void Deserialize(const string& p_Buffer) override\
{\
    if (p_Buffer.size() == sizeof(type)) memcpy(this, p_Buffer.data(), sizeof(type));\
}
