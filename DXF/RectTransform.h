//-----------------------------------------------------------------------------
// File: RectTransform
//
// Desc: 화면상의 좌표로 오브젝트를 출력할 때 사용되는 컴포넌트
//
//		[Variables]
//		- parent: Parent 오브젝트의 RectTransform 컴포넌트
//		- childs: 해당 오브젝트의 Child 오브젝트의 RectTransform 컴포넌트 목록
//      - position: 해당 오브젝트의 위치
//      - rotation: 해당 오브젝트의 회전 값
//      - scale: 해당 오브젝트의 크기 배율
//      - size: 해당 오브젝트를 출력할 때 표시될 사각형의 크기
//              (scale이 (1, 1, 1)일 때 기준)
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
    RectTransform*          parent = nullptr;
    vector<RectTransform*>  childs;

public:
    D3DXVECTOR2             position;
    D3DXVECTOR3             rotation;
    D3DXVECTOR2             scale;
    D3DXVECTOR2             size;

public:
    RectTransform(GameObject*, D3DXVECTOR2, D3DXVECTOR3, D3DXVECTOR2, D3DXVECTOR2);
    ~RectTransform();

    D3DXVECTOR2 GetScreenPosition();
    D3DXVECTOR3 GetScreenRotation();
    D3DXVECTOR2 GetScreenScale();

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