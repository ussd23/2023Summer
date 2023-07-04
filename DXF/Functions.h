//-----------------------------------------------------------------------------
// File: Functions
//
// Desc: DXF ������ ��� ������ �پ��� �Լ��� �����ϰ� ����.
//
//      [Functions]
//      - Lerp: ���� ���� (�� �� ������ �߰����� ��ȯ)
//      - Inner: 2���� ���� �ȿ� �ش� ��ǥ�� �����ִ� ���� ���� ��ȯ
//      - WorldToScreen: ����� ������Ʈ�� ��ġ�� ȭ��� ��ǥ�� ��ȯ
//      - GetDistance: �� ��ǥ ������ �Ÿ� ��ȯ
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
float Lerp(float, float, float);
bool Inner(RECT, D3DXVECTOR2);
D3DXVECTOR2 WorldToScreen(Transform*);
float GetDistance(D3DXVECTOR3, D3DXVECTOR3);

D3DXVECTOR3 SLerp(const D3DXVECTOR3*, const D3DXVECTOR3*, float);
D3DXVECTOR3 D3DXQuaternionToRotation(D3DXQUATERNION);
}

#define AddObjectToScene(object, parent, transform) g_Objects.push_back(object);\
        parent->AddChild(transform);
#define AddComponentToObject(object, component) object->AddComponent(component)
#define GetComponentFromObject(object, type) GameObject::Exists(object) ? dynamic_cast<type*>(object->GetComponent(#type)) : nullptr

#define SetInputBuffer(object, type, value) if (object.find(type) == object.end()) object.insert(make_pair(type, value));\
        else object[type] = value
#define GetInputBuffer(object, type) (object.find(type) == object.end()) ? false : object[type]