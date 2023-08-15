#include "ComponentHeader.h"
#include "Scripts.h"

void Sample3::InitObject() {
    //SceneManager::LoadScene("scene3");
    //return;

    // Manager
    GameObject* MineSweeper = new TextObject("MineSweeper", Vector2(600, 110), Vector2(300, 55), "맑은 고딕", 16, "");
    TopText* MS_Text = new TopText();
    AddComponentToObject(MineSweeper, MS_Text);
    Minesweeper* MS_Manager = new Minesweeper();
    AddComponentToObject(MineSweeper, MS_Manager);

    // MainCamera
    GameObject* Camera = new CameraObject("MainCamera", Vector3(0, 20, -10), Vector3(0, 1, 0));
    CameraMove* Camera_Move = new CameraMove(MS_Manager);
    AddComponentToObject(Camera, Camera_Move);

    // Button
    for (int i = 0; i < 3; i += 1) {
        GameObject* Button = new ButtonObject("Button", Vector2(100, 100), Vector2(50 + (i * 100), DXFGame::m_Resolution.y - 50), "Mine_Refresh.png");
        ResetButton* Button_Reset = new ResetButton(MS_Manager, i);
        AddComponentToObject(Button, Button_Reset);
        
        GameObject* Button_Text = new TextObject("Text", Vector2(100, 100), Vector2(10, 30), "맑은 고딕", 20, "");
        ResetButtonText* Text_Text = new ResetButtonText(i);
        AddComponentToObject(Button_Text, Text_Text);

        RectTransform* Button_Rect = GetComponentFromObject(Button, RectTransform);
        RectTransform* Button_Text_Rect = GetComponentFromObject(Button_Text, RectTransform);
        Button_Rect->AddChild(Button_Text_Rect);
    }

    SceneManager::SaveScene("scene3");
}
