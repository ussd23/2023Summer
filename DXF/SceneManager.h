#pragma once
#include "StandardLibrary.h"

class GameObject;

class SceneManager
{
protected:
	static void Parse(vector<string>* p_Comp, map<string, map<string, string>>* p_Object, string p_Line);
	static string Layer(string p_Key, map<string, map<string, string>>* p_Object, string p_Line);
	static GameObject* Initialize(vector<string>* p_Comp, map<string, map<string, string>>* p_Object);

public:
	static void SceneLoad(string p_Path);
};

