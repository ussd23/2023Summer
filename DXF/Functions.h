//-----------------------------------------------------------------------------
// File: Functions
//
// Desc: DXF ������ ��� ������ �پ��� �Լ��� �����ϰ� ����.
//
//      [Functions]
//      - Lerp: ���� ���� (�� �� ������ �߰����� ��ȯ)
//      - Inner: 2���� ���� �ȿ� �ش� ��ǥ�� �����ִ� ���� ���� ��ȯ
//      - WorldToScreen: ����� ������Ʈ�� ��ġ�� ȭ��� ��ǥ�� ��ȯ
//      - GetDistanceSquare: �� ��ǥ ������ �Ÿ��� ���� ��ȯ
//
//      [Macro]
//      - AddComponentToObject: ������Ʈ�� ������Ʈ �߰�
//      - GetComponentFromObject: ������Ʈ���� Ư�� ������Ʈ ��ȯ (�ش� ������Ʈ
//                                �Ǵ� ������Ʈ�� ���� ��� nullptr ��ȯ)
//      - SetInputBuffer: InputBuffer ���� (MsgProc������ ����ϱ� ����)
//      - GetInputBuffer: InputBuffer�� Ž���� ���ϴ� key�� ���� ��ȯ (�ش�Ǵ�
//                        key ���� ���� ��� false ��ȯ)
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
