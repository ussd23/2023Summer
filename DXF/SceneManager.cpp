#include <fstream>
#include "ComponentHeader.h"

#define GetData(string, data, conversion) if (tempmap.find(#string) != tempmap.end()) data = conversion(object->find(key)->second.find(#string)->second);

void SceneManager::SceneLoad(string _filepath)
{
    ifstream file;
    string path = "scenes\\" + _filepath;
    file.open(path);
    if (file.fail())
    {
        path = "..\\..\\scenes\\", _filepath;
        file.open(path);
        if (file.fail())
        {
            path = "..\\..\\scenes\\", _filepath;
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

void SceneManager::Parse(vector<string>* comp, map<string, map<string, string>>* object, string line)
{
    string value;

    while (0 != line.length())
    {
        for (int i = 0; i < line.length(); ++i)
        {
            if (',' == line[i])
            {
                value = line.substr(0, i);
                comp->push_back(value);
                line = line.substr(i + 1);
                break;
            }

            else if ('{' == line[i])
            {
                value = line.substr(0, i);
                comp->push_back(value);
                line = Layer(value, object, line.substr(i + 1));
                break;
            }
        }
    }
}

string SceneManager::Layer(string key, map<string, map<string, string>>* object, string line)
{
    int instant_key = 0;
    bool intstant_sw = true;
    string key2, value;
    map<string, string> temp;

    while (1)
    {
        for (int i = 0; i < line.length(); ++i)
        {
            if (':' == line[i])
            {
                key2 = line.substr(0, i);
                line = line.substr(i + 1);
                intstant_sw = false;
                break;
            }

            else if (',' == line[i] || '}' == line[i])
            {
                value = line.substr(0, i);

                if (intstant_sw)
                {
                    if ("Script" == key)
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

                if ('}' == line[i])
                {
                    object->insert(make_pair(key, temp));
                    return line.substr(i + 1);
                }

                line = line.substr(i + 1);
                break;
            }
        }
    }
}

// 수정 필요
GameObject* SceneManager::Initialize(vector<string>* comp, map<string, map<string, string>>* object)
{
    string objname = "";
    map<string, string> tempmap;

    GameObject* tempobj = new GameObject("");

    for (int i = 0; i < comp->size(); i++)
    {
        string key = comp->at(i);
        if (object->find(key) != object->end())
        {
            tempmap = object->find(key)->second;
        }

        if (key == "Name")
        {
            GetData(Value, objname);
            tempobj->name = objname;
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