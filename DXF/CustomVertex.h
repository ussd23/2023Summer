//-----------------------------------------------------------------------------
// File: CustomVertex
//
// Desc: VerticeRender에서 사용하는 CUSTOMVERTEX 구조체
//-----------------------------------------------------------------------------

#pragma once
#include "DXHeader.h"

struct CUSTOMVERTEX
{
    FLOAT x, y, z;
    DWORD color;
    FLOAT tu, tv;
};