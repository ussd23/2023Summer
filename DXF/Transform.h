//-----------------------------------------------------------------------------
// File: Transform
//
// Desc: 월드상의 좌표로 오브젝트를 출력할 때 사용되는 컴포넌트
//
//		[Variables]
//		- parent: Parent 오브젝트의 Transform 컴포넌트
//		- childs: 해당 오브젝트의 Child 오브젝트의 Transform 컴포넌트 목록
//      - position: 해당 오브젝트의 위치
//      - rotation: 해당 오브젝트의 회전 값
//      - scale: 해당 오브젝트의 크기 배율
//
//      [Functions]
//      - GetScreenPosition: Parent 오브젝트의 위치를 기준으로 현재 오브젝트의
//                           월드상 좌표를 반환
//      - GetScreenRotation: Parent 오브젝트의 회전 값을 기준으로 현재 오브젝트의
//                           월드상 회전 값을 반환
//      - GetScreenScale: Parent 오브젝트의 크기 배율을 기준으로 현재 오브젝트의
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