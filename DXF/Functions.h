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
//      - AddObjectToScene: ������Ʈ�� ó�� ������ ���
//      - AddComponentToObject: ������Ʈ�� ������Ʈ �߰�
//      - GetComponentFromObject: ������Ʈ���� Ư�� ������Ʈ ��ȯ (�ش� ������Ʈ
//                                �Ǵ� ������Ʈ�� ���� ��� nullptr ��ȯ)
//      - SetInputBuffer: InputBuffer ���� (MsgProc������ ����ϱ� ����)
//      - GetInputBuffer: InputBuffer�� Ž���� ���ϴ� key�� ���� ��ȯ (�ش�Ǵ�
//                        key ���� ���� ��� false ��ȯ)
//-----------------------------------------------------------------------------

#pragma once
#include "DXHeader.h"

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
Vector3 D3DXQuaternionToRotation(Quaternion p_Quaternion);
}

template <typename T> T Functions::Lerp(T p_Start, T p_End, float p_LerpT)
{
    return p_Start + p_LerpT * (p_End - p_Start);
}

#define AddObjectToScene(object, parent, transform) g_Objects.push_back(object);\
        parent->AddChild(transform);
#define AddComponentToObject(object, component) object->AddComponent(component)
#define GetComponentFromObject(object, type) GameObject::Exists(object) ? dynamic_cast<type*>(object->GetComponent(#type)) : nullptr

#define SetInputBuffer(object, type, value) if (object.find(type) == object.end()) object.insert(make_pair(type, value));\
        else object[type] = value
#define GetInputBuffer(object, type) (object.find(type) == object.end()) ? false : object[type]


