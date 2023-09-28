#pragma once
#include "DXHeader.h"
#include "CustomVertex.h"
#include "StandardLibrary.h"
#include "ComponentManager.h"
#include "json.h"

class Serializable;

#define SerializeFunction(type) \
type() = default;\
void JsonFunction(Json::Value& p_JsonValue, const bool& p_Mode) override

#define Serialize(value) if (p_Mode) InnerSerialzeFunction(p_JsonValue[#value], &value);\
else InnerDeserialzeFunction(p_JsonValue[#value], &value);
#define VectorSerialize(value) if (p_Mode) InnerVectorSerialzeFunction(p_JsonValue[#value], value);\
else InnerVectorDeserialzeFunction(p_JsonValue[#value], value);

#define SuperSerialize(value) if (p_Mode) InnerSuperSerialzeFunction(p_JsonValue[#value], value);\
else InnerSuperDeserialzeFunction(p_JsonValue[#value], value);
#define SuperVectorSerialize(value) if (p_Mode) InnerSuperVectorSerialzeFunction(p_JsonValue[#value], value);\
else InnerSuperVectorDeserialzeFunction(p_JsonValue[#value], value);

#define SuperSerializePtr(value) if (p_Mode) InnerSuperSerialzePtrFunction(p_JsonValue[#value], value);\
else InnerSuperDeserialzePtrFunction(p_JsonValue[#value], value);
#define SuperVectorSerializePtr(value) if (p_Mode) InnerSuperVectorSerialzePtrFunction(p_JsonValue[#value], value);\
else InnerSuperVectorDeserialzePtrFunction(p_JsonValue[#value], value);

#define ComponentSerialize(value) if (p_Mode) ComponentSerialzeFunction(p_JsonValue[#value], value);\
else ComponentDeserialzeFunction(p_JsonValue[#value], value);

class Serializable
{
protected:
    void InnerSerialzeFunction(Json::Value& p_JsonValue, int* p_Value);
    void InnerDeserialzeFunction(Json::Value& p_JsonValue, int* p_Value);
    void InnerSerialzeFunction(Json::Value& p_JsonValue, unsigned int* p_Value);
    void InnerDeserialzeFunction(Json::Value& p_JsonValue, unsigned int* p_Value);
    void InnerSerialzeFunction(Json::Value& p_JsonValue, long* p_Value);
    void InnerDeserialzeFunction(Json::Value& p_JsonValue, long* p_Value);
    void InnerSerialzeFunction(Json::Value& p_JsonValue, unsigned long* p_Value);
    void InnerDeserialzeFunction(Json::Value& p_JsonValue, unsigned long* p_Value);
    void InnerSerialzeFunction(Json::Value& p_JsonValue, long long* p_Value);
    void InnerDeserialzeFunction(Json::Value& p_JsonValue, long long* p_Value);
    void InnerSerialzeFunction(Json::Value& p_JsonValue, unsigned long long* p_Value);
    void InnerDeserialzeFunction(Json::Value& p_JsonValue, unsigned long long* p_Value);
    void InnerSerialzeFunction(Json::Value& p_JsonValue, float* p_Value);
    void InnerDeserialzeFunction(Json::Value& p_JsonValue, float* p_Value);
    void InnerSerialzeFunction(Json::Value& p_JsonValue, double* p_Value);
    void InnerDeserialzeFunction(Json::Value& p_JsonValue, double* p_Value);
    void InnerSerialzeFunction(Json::Value& p_JsonValue, bool* p_Value);
    void InnerDeserialzeFunction(Json::Value& p_JsonValue, bool* p_Value);
    void InnerSerialzeFunction(Json::Value& p_JsonValue, string* p_Value);
    void InnerDeserialzeFunction(Json::Value& p_JsonValue, string* p_Value);
    void InnerSerialzeFunction(Json::Value& p_JsonValue, Vector2* p_Value);
    void InnerDeserialzeFunction(Json::Value& p_JsonValue, Vector2* p_Value);
    void InnerSerialzeFunction(Json::Value& p_JsonValue, Vector3* p_Value);
    void InnerDeserialzeFunction(Json::Value& p_JsonValue, Vector3* p_Value);
    void InnerSerialzeFunction(Json::Value& p_JsonValue, Vector4* p_Value);
    void InnerDeserialzeFunction(Json::Value& p_JsonValue, Vector4* p_Value);
    void InnerSerialzeFunction(Json::Value& p_JsonValue, Quaternion* p_Value);
    void InnerDeserialzeFunction(Json::Value& p_JsonValue, Quaternion* p_Value);
    void InnerSerialzeFunction(Json::Value& p_JsonValue, Vertex* p_Value);
    void InnerDeserialzeFunction(Json::Value& p_JsonValue, Vertex* p_Value);

    template <typename T> void InnerSerialzeFunction(Json::Value& p_JsonValue, T* p_Value);
    template <typename T> void InnerDeserialzeFunction(Json::Value& p_JsonValue, T* p_Value);
    template <typename T> void InnerVectorSerialzeFunction(Json::Value& p_JsonValue, vector<T>& p_Value);
    template <typename T> void InnerVectorDeserialzeFunction(Json::Value& p_JsonValue, vector<T>& p_Value);

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Serializable, T>>> void InnerSuperSerialzeFunction(Json::Value& p_JsonValue, T& p_Value);
    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Serializable, T>>> void InnerSuperDeserialzeFunction(Json::Value& p_JsonValue, T& p_Value);
    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Serializable, T>>> void InnerSuperVectorSerialzeFunction(Json::Value& p_JsonValue, vector<T>& p_Value);
    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Serializable, T>>> void InnerSuperVectorDeserialzeFunction(Json::Value& p_JsonValue, vector<T>& p_Value);

    // 동적 할당된 객체에 사용할 수 있으나 메모리 누수 관리가 되지 않음에 유의
    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Serializable, T>>> void InnerSuperSerialzePtrFunction(Json::Value& p_JsonValue, T* p_Value);
    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Serializable, T>>> void InnerSuperDeserialzePtrFunction(Json::Value& p_JsonValue, T* p_Value);
    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Serializable, T>>> void InnerSuperVectorSerialzePtrFunction(Json::Value& p_JsonValue, vector<T*>& p_Value);
    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Serializable, T>>> void InnerSuperVectorDeserialzePtrFunction(Json::Value& p_JsonValue, vector<T*>& p_Value);

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Serializable, T>>> void ComponentSerialzeFunction(Json::Value& p_JsonValue, vector<T*>& p_Value);
    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Serializable, T>>> void ComponentDeserialzeFunction(Json::Value& p_JsonValue, vector<T*>& p_Value);

public:
    void JsonSerialize(Json::Value& p_JsonValue);
    void JsonDeserialize(Json::Value& p_JsonValue);
    virtual void JsonFunction(Json::Value& p_JsonValue, const bool& p_Mode) = 0;
};

template <typename T> void Serializable::InnerSerialzeFunction(Json::Value& p_JsonValue, T* p_Value)
{
    p_JsonValue = string(reinterpret_cast<const char*>(p_Value), sizeof(T));
}

template <typename T> void Serializable::InnerDeserialzeFunction(Json::Value& p_JsonValue, T* p_Value)
{
    memcpy(p_Value, p_JsonValue.asString().data(), sizeof(T));
}

template <typename T> void Serializable::InnerVectorSerialzeFunction(Json::Value& p_JsonValue, vector<T>& p_Value)
{
    for (int i = 0; i < p_Value.size(); ++i)
    {
        Json::Value result;
        T value = p_Value[i];
        InnerSerialzeFunction(result, &value);

        p_JsonValue.append(result);
    }
}

template <typename T> void Serializable::InnerVectorDeserialzeFunction(Json::Value& p_JsonValue, vector<T>& p_Value)
{
    p_Value.clear();
    for (unsigned int i = 0; i < p_JsonValue.size(); ++i)
    {
        T value;
        InnerDeserialzeFunction(p_JsonValue[i], &value);
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
    p_Value.clear();
    for (unsigned int i = 0; i < p_JsonValue.size(); ++i)
    {
        T value;
        value.JsonDeserialize(p_JsonValue[i]);

        p_Value.push_back(value);
    }
}

template <typename T, typename> void Serializable::InnerSuperSerialzePtrFunction(Json::Value& p_JsonValue, T* p_Value)
{ 
    Json::Value result;
    p_Value->JsonSerialize(result);
    p_JsonValue = result;
}

template <typename T, typename> void Serializable::InnerSuperDeserialzePtrFunction(Json::Value& p_JsonValue, T* p_Value)
{
    p_Value->JsonDeserialize(p_JsonValue);
}

template <typename T, typename> void Serializable::InnerSuperVectorSerialzePtrFunction(Json::Value& p_JsonValue, vector<T*>& p_Value)
{
    for (int i = 0; i < p_Value.size(); ++i)
    {
        Json::Value result;
        p_Value[i]->JsonSerialize(result);

        p_JsonValue.append(result);
    }
}

template <typename T, typename> void Serializable::InnerSuperVectorDeserialzePtrFunction(Json::Value& p_JsonValue, vector<T*>& p_Value)
{
    p_Value.clear();
    for (unsigned int i = 0; i < p_JsonValue.size(); ++i)
    {
        T* value = new T;
        value->JsonDeserialize(p_JsonValue[i]);

        p_Value.push_back(value);
    }
}

template <typename T, typename> void Serializable::ComponentSerialzeFunction(Json::Value& p_JsonValue, vector<T*>& p_Value)
{
    for (int i = 0; i < p_Value.size(); ++i)
    {
        Json::Value result;
        p_Value[i]->JsonSerialize(result["values"]);

        result["type"] = typeid(*p_Value[i]).name();

        p_JsonValue.append(result);
    }
}

template <typename T, typename> void Serializable::ComponentDeserialzeFunction(Json::Value& p_JsonValue, vector<T*>& p_Value)
{
    for (unsigned int i = 0; i < p_JsonValue.size(); ++i)
    {
        T* value = ComponentManager::CreateComponent(p_JsonValue[i]["type"].asString());
        if (value == nullptr) continue;

        value->JsonDeserialize(p_JsonValue[i]["values"]);

        p_Value.push_back(value);
    }
}