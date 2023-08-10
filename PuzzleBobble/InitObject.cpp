﻿#include "ComponentHeader.h"
#include "Scripts.h"

void PuzzleBobble::InitObject()
{
    //SceneManager::LoadScene("PuzzleBobble");

    //return;

    // MainCamera
    GameObject* gameObject = new CameraObject("MainCamera", Vector3(0, 0, -41), Vector3(0, 1, 0));
    CameraMove* cmove = new CameraMove();
    AddComponentToObject(gameObject, cmove);

    // Sun (Player)
    gameObject = new MeshObject("red", Vector3(0, -6.1, -8), "PuzzleBobble\\red.x");
    SphereCollider* scollider = new SphereCollider(1.2f);
    AddComponentToObject(gameObject, scollider);

    int level1[4][8] =
    {
        {1, 1, 2, 2, 3, 3, 4, 4},
        {1, 1, 2, 2, 3, 3, 4, 0},
        {3, 3, 4, 4, 1, 1, 2, 2},
        {3, 4, 4, 1, 1, 2, 2, 0}
    };

    Vector3 pos = Vector3(-7.2, 12, -8);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            switch (level1[i][j])
            {
            case 1:
                gameObject = new MeshObject("bubble", pos, "PuzzleBobble\\red.x");
                scollider = new SphereCollider(1.2f);
                AddComponentToObject(gameObject, scollider);
                break;
            case 2:
                gameObject = new MeshObject("bubble", pos, "PuzzleBobble\\green.x");
                scollider = new SphereCollider(1.2f);
                AddComponentToObject(gameObject, scollider);
                break;
            case 3:
                gameObject = new MeshObject("bubble", pos, "PuzzleBobble\\blue.x");
                scollider = new SphereCollider(1.2f);
                AddComponentToObject(gameObject, scollider);
                break;
            case 4:
                gameObject = new MeshObject("bubble", pos, "PuzzleBobble\\yellow.x");
                scollider = new SphereCollider(1.2f);
                AddComponentToObject(gameObject, scollider);
                break;
            }

            pos.x += 2.05;
        }

        if (i % 2 == 0) pos.x = -6.15;
        else pos.x = -7.2;

        pos.y -= 1.9;
    }

    // 화살표
    gameObject = new SpriteObject("empty", Vector2(0, 0), Vector2(SCREENSIZEX * 0.5 + 11, 750), "system\\default.png");
    Controll* controll = new Controll();
    AddComponentToObject(gameObject, controll);

    GameObject* childObject = new SpriteObject("arrow", Vector2(50, 100), Vector2(-25, -150), "PuzzleBobble\\arrow.png");
    RectTransform* parentrect = GetComponentFromObject(gameObject, RectTransform);
    RectTransform* childrect = GetComponentFromObject(childObject, RectTransform);
    childrect->SetParent(parentrect);

    SceneManager::SaveScene("PuzzleBobble");
}
