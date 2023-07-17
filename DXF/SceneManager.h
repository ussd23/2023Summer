#pragma once
#include "StandardLibrary.h"

class GameObject;

class SceneManager
{
protected:
	static void Parse(vector<string>*, map<string, map<string, string>>*, string);
	static string Layer(string, map<string, map<string, string>>*, string);
	static GameObject* Initialize(vector<string>*, map<string, map<string, string>>*);

public:
	static void SceneLoad(string);
};

