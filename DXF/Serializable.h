#pragma once
#include "DXHeader.h"
#include "StandardLibrary.h"

class Serializable
{
    virtual string Serialize() = 0;
    virtual void Deserialize(const string& p_Object) = 0;
};

