#include "Serializable.h"

void Serializable::InnerSerialzeFunction(Json::Value& p_JsonValue, int* p_Value)
{
	p_JsonValue = *p_Value;
}

void Serializable::InnerDeserialzeFunction(Json::Value& p_JsonValue, int* p_Value)
{
	*p_Value = p_JsonValue.asInt();
}

void Serializable::InnerSerialzeFunction(Json::Value& p_JsonValue, unsigned int* p_Value)
{
	p_JsonValue = *p_Value;
}

void Serializable::InnerDeserialzeFunction(Json::Value& p_JsonValue, unsigned int* p_Value)
{
	*p_Value = p_JsonValue.asUInt();
}

void Serializable::InnerSerialzeFunction(Json::Value& p_JsonValue, long long* p_Value)
{
	p_JsonValue = *p_Value;
}

void Serializable::InnerDeserialzeFunction(Json::Value& p_JsonValue, long long* p_Value)
{
	*p_Value = p_JsonValue.asInt64();
}

void Serializable::InnerSerialzeFunction(Json::Value& p_JsonValue, unsigned long long* p_Value)
{
	p_JsonValue = *p_Value;
}

void Serializable::InnerDeserialzeFunction(Json::Value& p_JsonValue, unsigned long long* p_Value)
{
	*p_Value = p_JsonValue.asUInt64();
}

void Serializable::InnerSerialzeFunction(Json::Value& p_JsonValue, float* p_Value)
{
	p_JsonValue = *p_Value;
}

void Serializable::InnerDeserialzeFunction(Json::Value& p_JsonValue, float* p_Value)
{
	*p_Value = p_JsonValue.asFloat();
}

void Serializable::InnerSerialzeFunction(Json::Value& p_JsonValue, double* p_Value)
{
	p_JsonValue = *p_Value;
}

void Serializable::InnerDeserialzeFunction(Json::Value& p_JsonValue, double* p_Value)
{
	*p_Value = p_JsonValue.asDouble();
}

void Serializable::InnerSerialzeFunction(Json::Value& p_JsonValue, bool* p_Value)
{
	p_JsonValue = *p_Value;
}

void Serializable::InnerDeserialzeFunction(Json::Value& p_JsonValue, bool* p_Value)
{
	*p_Value = p_JsonValue.asBool();
}

void Serializable::InnerSerialzeFunction(Json::Value& p_JsonValue, string* p_Value)
{
	p_JsonValue = *p_Value;
}

void Serializable::InnerDeserialzeFunction(Json::Value& p_JsonValue, string* p_Value)
{
	*p_Value = p_JsonValue.asString();
}

void Serializable::InnerSerialzeFunction(Json::Value& p_JsonValue, Vector2* p_Value)
{
	p_JsonValue["x"] = p_Value->x;
	p_JsonValue["y"] = p_Value->y;
}

void Serializable::InnerDeserialzeFunction(Json::Value& p_JsonValue, Vector2* p_Value)
{
	p_Value->x = p_JsonValue["x"].asFloat();
	p_Value->y = p_JsonValue["y"].asFloat();
}

void Serializable::InnerSerialzeFunction(Json::Value& p_JsonValue, Vector3* p_Value)
{
	p_JsonValue["x"] = p_Value->x;
	p_JsonValue["y"] = p_Value->y;
	p_JsonValue["z"] = p_Value->z;
}

void Serializable::InnerDeserialzeFunction(Json::Value& p_JsonValue, Vector3* p_Value)
{
	p_Value->x = p_JsonValue["x"].asFloat();
	p_Value->y = p_JsonValue["y"].asFloat();
	p_Value->z = p_JsonValue["z"].asFloat();
}

void Serializable::InnerSerialzeFunction(Json::Value& p_JsonValue, Vector4* p_Value)
{
	p_JsonValue["x"] = p_Value->x;
	p_JsonValue["y"] = p_Value->y;
	p_JsonValue["z"] = p_Value->z;
	p_JsonValue["w"] = p_Value->w;
}

void Serializable::InnerDeserialzeFunction(Json::Value& p_JsonValue, Vector4* p_Value)
{
	p_Value->x = p_JsonValue["x"].asFloat();
	p_Value->y = p_JsonValue["y"].asFloat();
	p_Value->z = p_JsonValue["z"].asFloat();
	p_Value->w = p_JsonValue["w"].asFloat();
}

void Serializable::InnerSerialzeFunction(Json::Value& p_JsonValue, Quaternion* p_Value)
{
	p_JsonValue["x"] = p_Value->x;
	p_JsonValue["y"] = p_Value->y;
	p_JsonValue["z"] = p_Value->z;
	p_JsonValue["w"] = p_Value->w;
}

void Serializable::InnerDeserialzeFunction(Json::Value& p_JsonValue, Quaternion* p_Value)
{
	p_Value->x = p_JsonValue["x"].asFloat();
	p_Value->y = p_JsonValue["y"].asFloat();
	p_Value->z = p_JsonValue["z"].asFloat();
	p_Value->w = p_JsonValue["w"].asFloat();
}
