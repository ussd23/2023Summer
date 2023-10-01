//-----------------------------------------------------------------------------
// File: RectTransform
//
// Desc: 화면상의 좌표로 오브젝트를 출력할 때 사용되는 컴포넌트
//
//		[Variables]
//		- m_Parent: Parent 오브젝트의 RectTransform 컴포넌트
//		- m_Childs: 해당 오브젝트의 Child 오브젝트의 RectTransform 컴포넌트 목록
//      - m_ScreenPosition: 해당 오브젝트의 스크린상 위치
//      - m_ScreenRotation: 해당 오브젝트의 스크린상 회전 값
//      - m_ScreenScale: 해당 오브젝트의 스크린상 크기 배율
//      - m_Position: 해당 오브젝트의 위치
//      - m_Rotation: 해당 오브젝트의 회전 값
//      - m_Scale: 해당 오브젝트의 크기 배율
//      - m_Size: 해당 오브젝트를 출력할 때 표시될 사각형의 크기
//              (scale이 (1, 1, 1)일 때 기준)
//
//      [Functions]
//      - SetScreenPosition: GetScreenPosition 값을 구하는 내부 함수
//      - SetScreenRotation: GetScreenRotation 값을 구하는 내부 함수
//      - SetScreenScale: GetScreenScale 값을 구하는 내부 함수
//      - GetScreenPosition: Parent 오브젝트의 위치를 기준으로 현재 오브젝트의
//                           스크린상 좌표를 반환
//      - GetScreenRotation: Parent 오브젝트의 회전 값을 기준으로 현재 오브젝트의
//                           스크린상 회전 값을 반환
//      - GetScreenScale: Parent 오브젝트의 크기 배율을 기준으로 현재 오브젝트의
//                        스크린상 크기 배율을 반환
//
//      - GetChildCount: Child 오브젝트의 개수 반환
//      - GetChild: 특정 인덱스의 Child 오브젝트의 RectTransform 컴포넌트 반환
//      - GetParent: Parent 오브젝트의 RectTransform 컴포넌트 반환
//      - FindChild: 컴포넌트를 기반으로 Child 오브젝트의 해당 컴포넌트 반환
//
//      [안전 업데이트가 반영되지 않은 함수]
//      - AddChild: Child로 추가
//      - AddChildAsFirst: 첫 번째 Child로 추가
//      - RemoveChild: Child 목록에서 제거
//      - SetAsFirstSibling: 첫 번째 Child로 변경
//      - SetAsLastSibling: 마지막 Child로 변경
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
    Vector2                 m_ScreenPosition;
    Quaternion              m_ScreenRotation;
    Vector2                 m_ScreenScale;
    Vector2                 m_Position;
    Quaternion              m_Rotation;
    Vector2                 m_Scale;
    vector<int>             m_ChildID;

public:
    Vector2                 m_Size;

protected:
    void SetScreenPosition();
    void SetScreenRotation();
    void SetScreenScale();

public:
    RectTransform(Vector2 p_Position, Vector3 p_Rotation, Vector2 p_Scale, Vector2 p_Size);

    void ScreenUpdate();
    Vector2 GetScreenPosition();
    Quaternion GetScreenRotation();
    Vector2 GetScreenScale();

    Vector2 GetPosition();
    Quaternion GetRotation();
    Vector2 GetScale();
    void SetPosition(Vector2 p_Position);
    void SetRotation(Quaternion p_Rotation);
    void SetScale(Vector2 p_Scale);

    int GetChildCount();
    vector<int> GetChildID();
    RectTransform* GetChild(int p_Index);
    RectTransform* GetParent();
    void SetParent(RectTransform* p_Parent);
    template <class T> void FindChild(T* p_Comp);

    void AddChild(RectTransform* p_Child);
    void AddChildAsFirst(RectTransform* p_Child);
    void RemoveChild(RectTransform* p_Child);
    void SetAsFirstSibling();
    void SetAsLastSibling();

    void Start() override;
    void OnEditorUpdate() override;

    SerializeFunction(RectTransform)
    {
        if (p_Mode)
        {
            m_ChildID.clear();
            for (int i = 0; i < m_Childs.size(); ++i) m_ChildID.push_back(GameObject::ObjectID(m_Childs[i]));
        }
        VectorSerialize(m_ChildID);
        Serialize(m_Position);
        if (p_Mode)
        {
            Vector3 m_RotationEuler = Functions::QuaternionToEuler(m_Rotation);
            Serialize(m_RotationEuler);
        }
        else
        {
            Vector3 m_RotationEuler;
            Serialize(m_RotationEuler);
            m_Rotation = Functions::EulerToQuaternion(m_RotationEuler);
        }
        Serialize(m_Scale);
        Serialize(m_Size);
    }
};

template <class T> void RectTransform::FindChild(T* p_Comp)
{
    for (int i = 0; i < m_Childs.size(); ++i)
    {
        T* comp = GetComponentFromObject(m_Childs[i]->gameObject, T);

        if (comp != nullptr) return m_Childs[i];
    }
}