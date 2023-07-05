#include "Scripts.h"

void TopText::Start()
{
    text = GetComponentFromObject(gameObject, TextRenderer);
    camera = Camera::main;
}

void TopText::Update()
{
    if (text == nullptr) return;
    if (camera == nullptr) return;

    Transform* transform = GetComponentFromObject(PlayerMove::player->gameObject, Transform);
    if (transform == nullptr) return;
    PlayerMove* playermove = GetComponentFromObject(PlayerMove::player->gameObject, PlayerMove);
    if (playermove == nullptr) return;

    D3DXVECTOR3 wpos = transform->GetWorldPosition();
    D3DXVECTOR2 spos = Functions::WorldToScreen(transform);

    stringstream temp;
    temp << fixed << setprecision(2) << "[FPS: " << Time::framePerSec << " / AvgFPS: " << Time::avgFrame << "]\n"\
        << "W/A/S/D: 이동, Q/E: 회전, R/F: 확대/축소\n[" << (camera->fovRate * 100)\
        << "%] 마우스 휠: 줌인/줌아웃, 우클릭: 카메라 포커스\n이 텍스트 혹은 플레이어 오브젝트를 클릭하면 메시지박스 출력";
    if (playermove->triggered) temp << " (충돌중)";
    temp << "\n플레이어 좌표: 월드 (" << wpos.x << ", " << wpos.y << ", " << wpos.z << ") / 화면 (" << spos.x << ", " << spos.y << ")";

    text->text = temp.str();
}

void TopText::OnMouseClick()
{
    MessageBox(NULL, "OnMouseClick() 실행됨", "TopText", MB_OK);
}