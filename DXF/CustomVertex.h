//-----------------------------------------------------------------------------
// File: Vertex
//
// Desc: VerticeRender���� ����ϴ� Custom Vertex ����ü
//-----------------------------------------------------------------------------

#pragma once
#include "DXHeader.h"

struct Vertex
{
    FLOAT x, y, z;
    DWORD color;
    FLOAT tu, tv;

    static const int FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;
};