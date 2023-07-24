//-----------------------------------------------------------------------------
// File: RectTransform
//
// Desc: ȭ����� ��ǥ�� ������Ʈ�� ����� �� ���Ǵ� ������Ʈ
//
//		[Variables]
//		- m_Parent: Parent ������Ʈ�� RectTransform ������Ʈ
//		- m_Childs: �ش� ������Ʈ�� Child ������Ʈ�� RectTransform ������Ʈ ���
//      - m_ScreenPosition: �ش� ������Ʈ�� ��ũ���� ��ġ
//      - m_ScreenRotation: �ش� ������Ʈ�� ��ũ���� ȸ�� ��
//      - m_ScreenScale: �ش� ������Ʈ�� ��ũ���� ũ�� ����
//      - m_Position: �ش� ������Ʈ�� ��ġ
//      - m_Rotation: �ش� ������Ʈ�� ȸ�� ��
//      - m_Scale: �ش� ������Ʈ�� ũ�� ����
//      - m_Size: �ش� ������Ʈ�� ����� �� ǥ�õ� �簢���� ũ��
//              (scale�� (1, 1, 1)�� �� ����)
//
//      [Functions]
//      - SetScreenPosition: GetScreenPosition ���� ���ϴ� ���� �Լ�
//      - SetScreenRotation: GetScreenRotation ���� ���ϴ� ���� �Լ�
//      - SetScreenScale: GetScreenScale ���� ���ϴ� ���� �Լ�
//      - GetScreenPosition: Parent ������Ʈ�� ��ġ�� �������� ���� ������Ʈ��
//                           ��ũ���� ��ǥ�� ��ȯ
//      - GetScreenRotation: Parent ������Ʈ�� ȸ�� ���� �������� ���� ������Ʈ��
//                           ��ũ���� ȸ�� ���� ��ȯ
//      - GetScreenScale: Parent ������Ʈ�� ũ�� ������ �������� ���� ������Ʈ��
//                        ��ũ���� ũ�� ������ ��ȯ
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
    RectTransform*          m_Parent = nullptr;
    vector<RectTransform*>  m_Childs;
    Vector2                 m_WorldPosition;
    Vector3                 m_WorldRotation;
    Vector2                 m_WorldScale;

public:
    Vector2                 m_Position;
    Vector3                 m_Rotation;
    Vector2                 m_Scale;
    Vector2                 m_Size;

protected:
    Vector2 SetScreenPosition();
    Vector3 SetScreenRotation();
    Vector2 SetScreenScale();

public:
    RectTransform(Vector2 p_Position, Vector3 p_Rotation, Vector2 p_Scale, Vector2 p_Size);

    Vector2 GetScreenPosition();
    Vector3 GetScreenRotation();
    Vector2 GetScreenScale();

    int GetChildCount();
    RectTransform* GetChild(int p_Index);
    RectTransform* GetParent();
    template <class T> void FindChild(T* p_Comp);

    void AddChild(RectTransform* p_Child);
    void AddChildAsFirst(RectTransform* p_Child);
    void RemoveChild(RectTransform* p_Child);
    void SetAsFirstSibling();
    void SetAsLastSibling();

    void Update() override;
};

template <class T> void RectTransform::FindChild(T* p_Comp)
{
    for (int i = 0; i < m_Childs.size(); ++i)
    {
        T* comp = GetComponentFromObject(m_Childs[i]->gameObject, T);

        if (comp != nullptr) return m_Childs[i];
    }
}