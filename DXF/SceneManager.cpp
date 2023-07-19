#include <fstream>
#include "ComponentHeader.h"

#define GetData(string, data, conversion) if (tempmap.find(#string) != tempmap.end()) data = conversion(p_Object->find(key)->second.find(#string)->second);

void SceneManager::SceneLoad(string p_Path)
{
    ifstream file;
    string path = "scenes\\" + p_Path;
    file.open(path);
    if (file.fail())
    {
        path = "..\\..\\scenes\\", p_Path;
        file.open(path);
        if (file.fail())
        {
            path = "..\\..\\scenes\\", p_Path;
            file.open(path);
            if (file.fail())
            {
                return;
            }
        }
    }

    while (!file.eof())
    {
        vector<string> comp;
        map<string, map<string, string>> object;
        string line;

        getline(file, line);
        while (line.size() > 0 && line.back() == '\\')
        {
            line.erase(--line.end());
            string templine;
            getline(file, templine);
            line += templine;
        }
        if ('\0' == line[0]) continue;
        if ('/' == line[0]) continue;

        Parse(&comp, &object, line);

        GameObject* gameObject = Initialize(&comp, &object);

        Transform* transform = GetComponentFromObject(gameObject, Transform);
        RectTransform* recttransform = GetComponentFromObject(gameObject, RectTransform);
        if (transform != nullptr)
        {
            AddObjectToScene(gameObject, g_RootTransform, transform);
        }
        else if (recttransform != nullptr)
        {
            AddObjectToScene(gameObject, g_RootRectTransform, recttransform);
        }
    }

    file.close();
}

void SceneManager::Parse(vector<string>* p_Comp, map<string, map<string, string>>* p_Object, string p_Line)
{
    string value;

    while (0 != p_Line.length())
    {
        for (int i = 0; i < p_Line.length(); ++i)
        {
            if (',' == p_Line[i])
            {
                value = p_Line.substr(0, i);
                p_Comp->push_back(value);
                p_Line = p_Line.substr(i + 1);
                break;
            }

            else if ('{' == p_Line[i])
            {
                value = p_Line.substr(0, i);
                p_Comp->push_back(value);
                p_Line = Layer(value, p_Object, p_Line.substr(i + 1));
                break;
            }
        }
    }
}

string SceneManager::Layer(string p_Key, map<string, map<string, string>>* p_Object, string p_Line)
{
    int instant_key = 0;
    bool intstant_sw = true;
    string key2, value;
    map<string, string> temp;

    while (1)
    {
        for (int i = 0; i < p_Line.length(); ++i)
        {
            if (':' == p_Line[i])
            {
                key2 = p_Line.substr(0, i);
                p_Line = p_Line.substr(i + 1);
                intstant_sw = false;
                break;
            }

            else if (',' == p_Line[i] || '}' == p_Line[i])
            {
                value = p_Line.substr(0, i);

                if (intstant_sw)
                {
                    if ("Script" == p_Key)
                    {
                        key2 = "Value";
                    }
                    else
                    {
                        key2 = to_string(++instant_key);
                    }
                }
                else
                {
                    intstant_sw = true;
                }

                temp.insert(make_pair(key2, value));

                if ('}' == p_Line[i])
                {
                    p_Object->insert(make_pair(p_Key, temp));
                    return p_Line.substr(i + 1);
                }

                p_Line = p_Line.substr(i + 1);
                break;
            }
        }
    }
}

// 수정 필요
GameObject* SceneManager::Initialize(vector<string>* p_Comp, map<string, map<string, string>>* p_Object)
{
    string objname = "";
    map<string, string> tempmap;

    GameObject* tempobj = new GameObject("");

    for (int i = 0; i < p_Comp->size(); i++)
    {
        string key = p_Comp->at(i);
        if (p_Object->find(key) != p_Object->end())
        {
            tempmap = p_Object->find(key)->second;
        }

        if (key == "Name")
        {
            GetData(Value, objname);
            tempobj->m_Name = objname;
        }

        else if (key == "Transform")
        {
            Vector3 position;
            Vector3 rotation;
            Vector3 scale;

            GetData(PosX, position.x, stof);
            GetData(PosY, position.y, stof);
            GetData(PosZ, position.z, stof);
            GetData(RotX, rotation.x, stof);
            GetData(RotY, rotation.y, stof);
            GetData(RotZ, rotation.z, stof);
            GetData(ScaX, scale.x, stof);
            GetData(ScaY, scale.y, stof);
            GetData(ScaZ, scale.z, stof);

            Transform* tempcomp = new Transform(position, rotation, scale);
            AddComponentToObject(tempobj, tempcomp);
        }

        else if (key == "RectTransform")
        {

        }

        else if (key == "Camera")
        {

        }

        else if (key == "MeshRenderer")
        {

        }

        else if (key == "VerticeRenderer")
        {

        }

        else if (key == "SpriteRenderer")
        {

        }

        else if (key == "TextRenderer")
        {

        }

        else if (key == "Animator")
        {

        }

        else if (key == "MouseFunction")
        {

        }

        else if (key == "BoxCollider")
        {

        }

        else if (key == "SphereCollider")
        {

        }
    }

    return tempobj;
}