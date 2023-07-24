//-----------------------------------------------------------------------------
// File: Transform
//
// Desc: ������� ��ǥ�� ������Ʈ�� ����� �� ���Ǵ� ������Ʈ
//
//		[Variables]
//		- m_Parent: Parent ������Ʈ�� Transform ������Ʈ
//		- m_Childs: �ش� ������Ʈ�� Child ������Ʈ�� Transform ������Ʈ ���
//      - m_WorldPosition: �ش� ������Ʈ�� ����� ��ġ
//      - m_WorldRotation: �ش� ������Ʈ�� ����� ȸ�� ��
//      - m_WorldScale: �ش� ������Ʈ�� ����� ũ�� ����
//      - m_Position: �ش� ������Ʈ�� ��ġ
//      - m_Rotation: �ش� ������Ʈ�� ȸ�� ��
//      - m_Scale: �ش� ������Ʈ�� ũ�� ����
//
//      [Functions]
//      - SetWorldPosition: GetWorldPosition ���� ���ϴ� ���� �Լ�
//      - SetWorldRotation: GetWorldRotation ���� ���ϴ� ���� �Լ�
//      - SetWorldScale: GetWorldScale ���� ���ϴ� ���� �Լ�
//      - GetWorldPosition: Parent ������Ʈ�� ��ġ�� �������� ���� ������Ʈ��
//                           ����� ��ǥ�� ��ȯ
//      - GetWorldRotation: Parent ������Ʈ�� ȸ�� ���� �������� ���� ������Ʈ��
//                           ����� ȸ�� ���� ��ȯ
//      - GetWorldScale: Parent ������Ʈ�� ũ�� ������ �������� ���� ������Ʈ��
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
    Transform*          m_Parent = nullptr;
    vector<Transform*>  m_Childs;
    Vector3             m_WorldPosition;
    Vector3             m_WorldRotation;
    Vector3             m_WorldScale;
    Vector3             m_Position;
    Vector3             m_Rotation;
    Vector3             m_Scale;

protected:
    Vector3 SetWorldPosition();
    Vector3 SetWorldRotation();
    Vector3 SetWorldScale();

public:
    Transform(Vector3 p_Position, Vector3 p_Rotation, Vector3 p_Scale);

    Vector3 GetWorldPosition();
    Vector3 GetWorldRotation();
    Vector3 GetWorldScale();

    Vector3 GetPosition();
    Vector3 GetRotation();
    Vector3 GetScale();
    void SetPosition(Vector3 p_Position);
    void SetRotation(Vector3 p_Rotation);
    void SetScale(Vector3 p_Scale);

    int GetChildCount();
    Transform* GetChild(int p_Index);
    Transform* GetParent();
    template <class T> void FindChild(T* p_Comp);

    void AddChild(Transform* p_Child);
    void AddChildAsFirst(Transform* p_Child);
    void RemoveChild(Transform* p_Child);
    void SetAsFirstSibling();
    void SetAsLastSibling();

    void PreUpdate() override;
};

template <class T> void Transform::FindChild(T* p_Comp)
{
    for (int i = 0; i < m_Childs.size(); ++i)
    {
        T* comp = GetComponentFromObject(m_Childs[i]->gameObject, T);

        if (comp != nullptr) return m_Childs[i];
    }
}