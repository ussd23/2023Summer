#include <fstream>
#include "ComponentHeader.h"

void SceneManager::SaveScene(string p_Name)
{
    Json::StyledStreamWriter writer;

    string path = "scenes\\" + p_Name + ".txt";
    ofstream json_dir(path.c_str());

    if (!json_dir.is_open())
    {
        path = "..\\scenes\\" + p_Name + ".txt";
        json_dir.open(path.c_str());
        if (!json_dir.is_open())
        {
            path = "..\\..\\scenes\\" + p_Name + ".txt";
            json_dir.open(path.c_str());
            if (!json_dir.is_open())
            {
                string text = "Could not save scene: " + p_Name;
                MessageBox(NULL, text.c_str(), "Scene Load Failed", MB_OK);
                return;
            }
        }
    }

	Json::Value scene;

    list<SPTR<GameObject>>::iterator iter = Var::Objects.begin();

	while (iter != Var::Objects.end())
	{
		Json::Value result;
        (*iter)()->JsonSerialize(result);

		scene.append(result);
        ++iter;
	}
	
	writer.write(json_dir, scene);
	
    json_dir.close();
}

void SceneManager::LoadScene(string p_Name)
{
    string path = "scenes\\" + p_Name + ".txt";
    ifstream json_dir(path.c_str());

    if (!json_dir.is_open())
    {
        path = "..\\scenes\\" + p_Name + ".txt";
        json_dir.open(path.c_str());
        if (!json_dir.is_open())
        {
            path = "..\\..\\scenes\\" + p_Name + ".txt";
            json_dir.open(path.c_str());
            if (!json_dir.is_open())
            {
                string text = "Could not find scene: " + p_Name;
                MessageBox(NULL, text.c_str(), "Scene Load Failed", MB_OK);
                return;
            }
        }
    }

    GameObject::Destroy(Var::RootObject);
    GameObject::Destroy(Var::RootRectObject);

    vector<GameObject*> objects;
    Json::Value scene;
    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;
    if (Json::parseFromStream(builder, json_dir, &scene, &errs))
    {
        for (unsigned int i = 0; i < scene.size(); ++i)
        {
            GameObject* object = new GameObject;

            object->JsonDeserialize(scene[i]);

            objects.push_back(object);
        }
    }

    if (objects.size() >= 1)
    {
        Var::RootObject = objects[0];
        Var::RootTransform = dynamic_cast<Transform*>(objects[0]->GetComponent("Transform"));
        Var::RootRectObject = objects[1];
        Var::RootRectTransform = dynamic_cast<RectTransform*>(objects[1]->GetComponent("RectTransform"));
    }

    for (int i = 0; i < objects.size(); ++i)
    {
        Transform* transform = dynamic_cast<Transform*>(objects[i]->GetComponent("Transform"));
        if (transform != nullptr)
        {
            vector<int> childID = transform->GetChildID();
            for (int j = 0; j < childID.size(); ++j)
            {
                transform->AddChild(dynamic_cast<Transform*>(objects[childID[j]]->GetComponent("Transform")));
            }

            continue;
        }

        RectTransform* recttransform = dynamic_cast<RectTransform*>(objects[i]->GetComponent("RectTransform"));
        if (recttransform != nullptr)
        {
            vector<int> childID = recttransform->GetChildID();
            for (int j = 0; j < childID.size(); ++j)
            {
                recttransform->AddChild(dynamic_cast<RectTransform*>(objects[childID[j]]->GetComponent("RectTransform")));
            }
        }
    }

    for (int i = 0; i < objects.size(); ++i)
    {
        Var::Objects.push_back(objects[i]);
    }
}
