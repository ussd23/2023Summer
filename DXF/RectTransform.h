//-----------------------------------------------------------------------------
// File: RectTransform
//
// Desc: ȭ����� ��ǥ�� ������Ʈ�� ����� �� ���Ǵ� ������Ʈ
//
//		[Variables]
//		- parent: Parent ������Ʈ�� RectTransform ������Ʈ
//		- childs: �ش� ������Ʈ�� Child ������Ʈ�� RectTransform ������Ʈ ���
//      - position: �ش� ������Ʈ�� ��ġ
//      - rotation: �ش� ������Ʈ�� ȸ�� ��
//      - scale: �ش� ������Ʈ�� ũ�� ����
//      - size: �ش� ������Ʈ�� ����� �� ǥ�õ� �簢���� ũ��
//              (scale�� (1, 1, 1)�� �� ����)
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
//      - GetChild: Ư�� �ε����� Child ������Ʈ�� RectTransform ������Ʈ ��ȯ
//      - GetParent: Parent ������Ʈ�� RectTransform ������Ʈ ��ȯ
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
#include "StandardLibrary.h"

class RectTransform : public Component
{
protected:
    RectTransform*          parent = nullptr;
    vector<RectTransform*>  childs;

public:
    Vector2                 position;
    Vector3                 rotation;
    Vector2                 scale;
    Vector2                 size;

public:
    RectTransform(GameObject*, Vector2, Vector3, Vector2, Vector2);

    Vector2 GetScreenPosition();
    Vector3 GetScreenRotation();
    Vector2 GetScreenScale();

    int GetChildCount();
    RectTransform* GetChild(int);
    RectTransform* GetParent();
    template <class T> void FindChild(T*);

    void AddChild(RectTransform*);
    void AddChildAsFirst(RectTransform*);
    void RemoveChild(RectTransform*);
    void SetAsFirstSibling();
    void SetAsLastSibling();
};

template <class T> void RectTransform::FindChild(T* _comp)
{
    for (int i = 0; i < childs.size(); ++i)
    {
        T* comp = GetComponentFromObject(childs[i]->gameObject, T);

        if (comp != nullptr) return childs[i];
    }
}