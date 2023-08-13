#include "ComponentHeader.h"
#include "Scripts.h"

void Sample3::InitObject() {
    //SceneManager::LoadScene("scene3");
    //return;

    // MainCamera
    GameObject* Camera = new CameraObject("MainCamera", Vector3(0, 20, -10), Vector3(0, 1, 0));
    CameraMove* Camera_Move = new CameraMove();
    AddComponentToObject(Camera, Camera_Move);

    // Manager
    GameObject* MineSweeper = new TextObject("MineSweeper", Vector2(600, 110), Vector2(300, 55), "맑은 고딕", 16, "");
    TopText* MS_Text = new TopText();
    AddComponentToObject(MineSweeper, MS_Text);
    Minesweeper* MS_Manager = new Minesweeper();
    AddComponentToObject(MineSweeper, MS_Manager);

    // Button
    GameObject* Button = new ButtonObject("Button", Vector2(100, 100), Vector2(50, DXFGame::m_Resolution.y - 50), "Mine_Refresh.png");
    ButtonTest* test = new ButtonTest(MS_Manager);
    AddComponentToObject(Button, test);

    SceneManager::SaveScene("scene3");
}
