#pragma once
#include "GameObject.h"

class EmptyObject : public GameObject
{
public:
	EmptyObject(string p_Name, Vector3 p_Position);
};

class EmptyRectObject : public GameObject
{
public:
	EmptyRectObject(string p_Name, Vector2 p_Size, Vector2 p_Position);
};

class CameraObject : public GameObject
{
public:
	CameraObject(string p_Name, Vector3 p_Position, Vector3 p_Destination);
};

class PlaneObject : public GameObject
{
protected:
	static vector<Vertex> m_Vector;

public:
	PlaneObject(string p_Name, Vector3 p_Position, string p_TextureName);
};

class MeshObject : public GameObject
{
public:
	MeshObject(string p_Name, Vector3 p_Position, string p_ModelName);
};

class SpriteObject : public GameObject
{
public:
	SpriteObject(string p_Name, Vector2 p_Size, Vector2 p_Position, string p_TextureName);
};

class TextObject : public GameObject
{
public:
	TextObject(string p_Name, Vector2 p_Size, Vector2 p_Position, string p_FontName, int p_FontSize, string p_Text);
};