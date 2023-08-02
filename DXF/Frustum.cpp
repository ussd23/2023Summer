#include "Frustum.h"
#include "Global.h"
#include "Functions.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Transform.h"
#include "Camera.h"

void Frustum::MakeFrustum(Matrix16* p_MatViewProj)
{
    m_Vertex[0] = Vector3(-1.0f, -1.0f, 0.0f);
    m_Vertex[1] = Vector3(1.0f, -1.0f, 0.0f);
    m_Vertex[2] = Vector3(1.0f, -1.0f, 1.0f);
    m_Vertex[3] = Vector3(-1.0f, -1.0f, 1.0f);
    m_Vertex[4] = Vector3(-1.0f, 1.0f, 0.0f);
    m_Vertex[5] = Vector3(1.0f, 1.0f, 0.0f);
    m_Vertex[6] = Vector3(1.0f, 1.0f, 1.0f);
    m_Vertex[7] = Vector3(-1.0f, 1.0f, 1.0f);

    Matrix16 matInv;
    D3DXMatrixInverse(&matInv, NULL, p_MatViewProj);

    for (int i = 0; i < 8; ++i)
    {
        D3DXVec3TransformCoord(&m_Vertex[i], &m_Vertex[i], &matInv);
    }

    // 절두체 평면 생성
    D3DXPlaneFromPoints(&m_Plane[0], &m_Vertex[4], &m_Vertex[7], &m_Vertex[6]);
    D3DXPlaneFromPoints(&m_Plane[1], &m_Vertex[0], &m_Vertex[1], &m_Vertex[2]);
    D3DXPlaneFromPoints(&m_Plane[2], &m_Vertex[0], &m_Vertex[4], &m_Vertex[5]);
    D3DXPlaneFromPoints(&m_Plane[3], &m_Vertex[2], &m_Vertex[6], &m_Vertex[7]);
    D3DXPlaneFromPoints(&m_Plane[4], &m_Vertex[0], &m_Vertex[3], &m_Vertex[7]);
    D3DXPlaneFromPoints(&m_Plane[5], &m_Vertex[1], &m_Vertex[5], &m_Vertex[6]);
}

bool Frustum::isIn(Vector3 p_Position)
{
    for (int i = 0 ; i < 6 ; ++i)
    {
        float fDist = D3DXPlaneDotCoord(&m_Plane[i], &p_Position);
        if (fDist > 0) return false;
    }

    ++Var::CullingObjects;
    return true;
}

bool Frustum::isIn(Vector3 p_Position, float p_Radius)
{
    for (int i = 0; i < 6; ++i)
    {
        float fDist = D3DXPlaneDotCoord(&m_Plane[i], &p_Position);
        if (fDist > (p_Radius + 0)) return false;
    }

    ++Var::CullingObjects;
    return true;
}