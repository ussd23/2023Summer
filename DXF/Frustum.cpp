#include "Frustum.h"
#include "Global.h"
#include "Functions.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Transform.h"
#include "Camera.h"

void Frustum::MakeFrustum(Matrix16* _pMatViewProj)
{
    vertex[0] = Vector3(-1.0f, -1.0f, 0.0f);
    vertex[1] = Vector3(1.0f, -1.0f, 0.0f);
    vertex[2] = Vector3(1.0f, -1.0f, 1.0f);
    vertex[3] = Vector3(-1.0f, -1.0f, 1.0f);
    vertex[4] = Vector3(-1.0f, 1.0f, 0.0f);
    vertex[5] = Vector3(1.0f, 1.0f, 0.0f);
    vertex[6] = Vector3(1.0f, 1.0f, 1.0f);
    vertex[7] = Vector3(-1.0f, 1.0f, 1.0f);

    Matrix16 matInv;
    D3DXMatrixInverse(&matInv, NULL, _pMatViewProj);

    for (int i = 0; i < 8; ++i)
    {
        D3DXVec3TransformCoord(&vertex[i], &vertex[i], &matInv);
    }

    // 절두체 평면 생성
    D3DXPlaneFromPoints(&plane[0], &vertex[4], &vertex[7], &vertex[6]);
    D3DXPlaneFromPoints(&plane[1], &vertex[0], &vertex[1], &vertex[2]);
    D3DXPlaneFromPoints(&plane[2], &vertex[0], &vertex[4], &vertex[5]);
    D3DXPlaneFromPoints(&plane[3], &vertex[2], &vertex[6], &vertex[7]);
    D3DXPlaneFromPoints(&plane[4], &vertex[0], &vertex[3], &vertex[7]);
    D3DXPlaneFromPoints(&plane[5], &vertex[1], &vertex[5], &vertex[6]);
}

bool Frustum::isIn(Vector3 _pos)
{
    for (int i = 0 ; i < 6 ; ++i)
    {
        float fDist = D3DXPlaneDotCoord(&plane[i], &_pos);
        if (fDist > 0) return false;
    }

    ++g_CullingObjects;
    return true;
}

bool Frustum::isIn(Vector3 _pos, float _radius)
{
    for (int i = 0; i < 6; ++i)
    {
        float fDist = D3DXPlaneDotCoord(&plane[i], &_pos);
        if (fDist > (_radius + 0)) return false;
    }

    ++g_CullingObjects;
    return true;
}