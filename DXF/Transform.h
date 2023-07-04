//-----------------------------------------------------------------------------
// File: Transform
//
// Desc: ������� ��ǥ�� ������Ʈ�� ����� �� ���Ǵ� ������Ʈ
//
//		[Variables]
//		- parent: Parent ������Ʈ�� Transform ������Ʈ
//		- childs: �ش� ������Ʈ�� Child ������Ʈ�� Transform ������Ʈ ���
//      - position: �ش� ������Ʈ�� ��ġ
//      - rotation: �ش� ������Ʈ�� ȸ�� ��
//      - scale: �ش� ������Ʈ�� ũ�� ����
//
//      [Functions]
//      - GetScreenPosition: Parent ������Ʈ�� ��ġ�� �������� ���� ������Ʈ��
//                           ����� ��ǥ�� ��ȯ
//      - GetScreenRotation: Parent ������Ʈ�� ȸ�� ���� �������� ���� ������Ʈ��
//                           ����� ȸ�� ���� ��ȯ
//      - GetScreenScale: Parent ������Ʈ�� ũ�� ������ �������� ���� ������Ʈ��
//                        ����� ũ�� ������ ��ȯ
//
//      - GetChildCount: Child ������Ʈ�� ���� ��ȯ
//      - GetChild: Ư�� �ε����� Child ������Ʈ�� Transform ������Ʈ ��ȯ
//      - GetParent: Parent ������Ʈ�� Transform ������Ʈ ��ȯ
//      - FindChild: ������Ʈ�� ������� Child ������Ʈ�� �ش� ������Ʈ ��ȯ
//
//      [���� ������Ʈ�� �ݿ����� ���� �Լ�]
//      - AddChild: Child�� �߰�
//      - AddChildAsFirst: ù ��° Child�� �߰�
//      - RemoveChild: Child ��Ͽ��� ����
//      - SetAsFirstSibling: ù ��° Child�� ����
//      - SetAsLastSibling: ������ Child�� ����
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "Functions.h"
#include "StandardLibrary.h"

class Transform : public Component
{
protected:
    Transform*          parent = nullptr;
    vector<Transform*>  childs;

public:
    D3DXVECTOR3         position;
    D3DXVECTOR3         rotation;
    D3DXVECTOR3         scale;

public:
    Transform(GameObject*, D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3);
    ~Transform();

    D3DXVECTOR3 GetWorldPosition();
    D3DXVECTOR3 GetWorldRotation();
    D3DXVECTOR3 GetWorldScale();

    int GetChildCount();
    Transform* GetChild(int);
    Transform* GetParent();
    template <class T> void FindChild(T*);

    void AddChild(Transform*);
    void AddChildAsFirst(Transform*);
    void RemoveChild(Transform*);
    void SetAsFirstSibling();
    void SetAsLastSibling();
};

template <class T> void Transform::FindChild(T* _comp)
{
    for (int i = 0; i < childs.size(); ++i)
    {
        T* comp = GetComponentFromObject(childs[i]->gameObject, T);

        if (comp != nullptr) return childs[i];
    }
}