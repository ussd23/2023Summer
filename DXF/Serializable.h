#pragma once
#include "DXHeader.h"
#include "StandardLibrary.h"
#include "json.h"

#define SerializeFunction(type) \
type() = default;\
void JsonSerialize(Json::Value& p_JsonValue) override
#define DeserializeFunction() \
void JsonDeserialize(Json::Value p_JsonValue) override

#define Serialize(value) p_JsonValue[#value] = string(reinterpret_cast<const char*>(&value), sizeof(value));
#define Deserialize(value) if (sizeof(value) == p_JsonValue[#value].asString().length()) memcpy(&value, p_JsonValue[#value].asString().data(), sizeof(value));

#define VectorSerialize(value) p_JsonValue[#value] = string(reinterpret_cast<const char*>(&value), sizeof(value) * value.size());
#define VectorDeserialize(value) if (sizeof(value) * value.size() == p_JsonValue[#value].asString().length()) memcpy(&value, p_JsonValue[#value].asString().data(), sizeof(value) * value.size());

class Serializable
{
public:
    virtual void JsonSerialize(Json::Value& p_JsonValue) = 0;
    virtual void JsonDeserialize(Json::Value p_JsonValue) = 0;
};