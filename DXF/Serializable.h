#pragma once
#include "DXHeader.h"
#include "StandardLibrary.h"
#include "json.h"

class Serializable;

#define SerializeFunction(type) \
type() = default;\
void JsonSerialize(Json::Value& p_JsonValue) override
#define DeserializeFunction() \
void JsonDeserialize(Json::Value p_JsonValue) override

#define Serialize(value) InnerSerialzeFunction(p_JsonValue[#value], &value);
#define Deserialize(value) InnerDeserialzeFunction(p_JsonValue[#value], &value);
#define VectorSerialize(value) InnerVectorSerialzeFunction(p_JsonValue[#value], value);
#define VectorDeserialize(value) InnerVectorDeserialzeFunction(p_JsonValue[#value], value);

#define SuperSerialize(value) InnerSuperSerialzeFunction(p_JsonValue[#value], value);
#define SuperDeserialize(value) InnerSuperDeserialzeFunction(p_JsonValue[#value], value);
#define SuperVectorSerialize(value) InnerSuperVectorSerialzeFunction(p_JsonValue[#value], value);
#define SuperVectorDeserialize(value) InnerSuperVectorDeserialzeFunction(p_JsonValue[#value], value);

class Serializable
{
protected:
    template <typename T> void InnerSerialzeFunction(Json::Value& p_JsonValue, T* p_Value);
    template <typename T> void InnerDeserialzeFunction(Json::Value& p_JsonValue, T* p_Value);
    template <typename T> void InnerVectorSerialzeFunction(Json::Value& p_JsonValue, vector<T>& p_Value);
    template <typename T> void InnerVectorDeserialzeFunction(Json::Value& p_JsonValue, vector<T>& p_Value);

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Serializable, T>>> void InnerSuperSerialzeFunction(Json::Value& p_JsonValue, T& p_Value);
    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Serializable, T>>> void InnerSuperDeserialzeFunction(Json::Value& p_JsonValue, T& p_Value);
    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Serializable, T>>> void InnerSuperVectorSerialzeFunction(Json::Value& p_JsonValue, vector<T>& p_Value);
    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Serializable, T>>> void InnerSuperVectorDeserialzeFunction(Json::Value& p_JsonValue, vector<T>& p_Value);

public:
    virtual void JsonSerialize(Json::Value& p_JsonValue) = 0;
    virtual void JsonDeserialize(Json::Value p_JsonValue) = 0;
};

template <typename T> void Serializable::InnerSerialzeFunction(Json::Value& p_JsonValue, T* p_Value)
{
    p_JsonValue = string(reinterpret_cast<const char*>(p_Value), sizeof(T));
}

template <typename T> void Serializable::InnerDeserialzeFunction(Json::Value& p_JsonValue, T* p_Value)
{
    if (sizeof(T) == p_JsonValue.asString().length()) memcpy(p_Value, p_JsonValue.asString().data(), sizeof(T));
}

template <typename T> void Serializable::InnerVectorSerialzeFunction(Json::Value& p_JsonValue, vector<T>& p_Value)
{
    for (int i = 0; i < p_Value.size(); ++i)
    {
        T value = p_Value[i];
        Json::Value result = string(reinterpret_cast<const char*>(&value), sizeof(T));

        p_JsonValue.append(result);
    }
}

template <typename T> void Serializable::InnerVectorDeserialzeFunction(Json::Value& p_JsonValue, vector<T>& p_Value)
{
    for (unsigned int i = 0; i < p_JsonValue.size(); ++i)
    {
        T value;
        if (sizeof(T) == p_JsonValue[i].asString().length()) memcpy(&value, p_JsonValue[i].asString().data(), sizeof(T));
        p_Value.push_back(value);
    }
}

template <typename T, typename> void Serializable::InnerSuperSerialzeFunction(Json::Value& p_JsonValue, T& p_Value)
{
    Json::Value result;
    p_Value.JsonSerialize(result);
    p_JsonValue = result;
}

template <typename T, typename> void Serializable::InnerSuperDeserialzeFunction(Json::Value& p_JsonValue, T& p_Value)
{
    p_Value.JsonDeserialize(p_JsonValue);
}

template <typename T, typename> void Serializable::InnerSuperVectorSerialzeFunction(Json::Value& p_JsonValue, vector<T>& p_Value)
{
    for (int i = 0; i < p_Value.size(); ++i)
    {
        Json::Value result;
        p_Value[i].JsonSerialize(result);

        p_JsonValue.append(result);
    }
}

template <typename T, typename> void Serializable::InnerSuperVectorDeserialzeFunction(Json::Value& p_JsonValue, vector<T>& p_Value)
{
    for (unsigned int i = 0; i < p_JsonValue.size(); ++i)
    {
        T value;
        value.JsonDeserialize(p_JsonValue[i]);

        p_Value.push_back(value);
    }
}