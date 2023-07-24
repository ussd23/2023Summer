//-----------------------------------------------------------------------------
// File: Transform
//
// Desc: 월드상의 좌표로 오브젝트를 출력할 때 사용되는 컴포넌트
//
//		[Variables]
//		- m_Parent: Parent 오브젝트의 Transform 컴포넌트
//		- m_Childs: 해당 오브젝트의 Child 오브젝트의 Transform 컴포넌트 목록
//      - m_WorldPosition: 해당 오브젝트의 월드상 위치
//      - m_WorldRotation: 해당 오브젝트의 월드상 회전 값
//      - m_WorldScale: 해당 오브젝트의 월드상 크기 배율
//      - m_Position: 해당 오브젝트의 위치
//      - m_Rotation: 해당 오브젝트의 회전 값
//      - m_Scale: 해당 오브젝트의 크기 배율
//
//      [Functions]
//      - SetWorldPosition: GetWorldPosition 값을 구하는 내부 함수
//      - SetWorldRotation: GetWorldRotation 값을 구하는 내부 함수
//      - SetWorldScale: GetWorldScale 값을 구하는 내부 함수
//      - GetWorldPosition: Parent 오브젝트의 위치를 기준으로 현재 오브젝트의
//                           월드상 좌표를 반환
//      - GetWorldRotation: Parent 오브젝트의 회전 값을 기준으로 현재 오브젝트의
//                           월드상 회전 값을 반환
//      - GetWorldScale: Parent 오브젝트의 크기 배율을 기준으로 현재 오브젝트의
//                        월드상 크기 배율을 반환
//
//      - GetChildCount: Child 오브젝트의 개수 반환
//      - GetChild: 특정 인덱스의 Child 오브젝트의 Transform 컴포넌트 반환
//      - GetParent: Parent 오브젝트의 Transform 컴포넌트 반환
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