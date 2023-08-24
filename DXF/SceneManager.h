#pragma once
#include "StandardLibrary.h"

class GameObject;

class SceneManager
{
public:
	static void SaveScene(string p_Name);
	static void LoadScene(string p_Name);
};

