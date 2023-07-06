//-----------------------------------------------------------------------------
// File: Vertex
//
// Desc: VerticeRender에서 사용하는 Custom Vertex 구조체
//-----------------------------------------------------------------------------

#pragma once
#include "DXHeader.h"

struct Vertex
{
    FLOAT x, y, z;
    DWORD color;
    FLOAT tu, tv;
};