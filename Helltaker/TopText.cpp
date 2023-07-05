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
        << "W/A/S/D: �̵�, Q/E: ȸ��, R/F: Ȯ��/���\n[" << (camera->fovRate * 100)\
        << "%] ���콺 ��: ����/�ܾƿ�, ��Ŭ��: ī�޶� ��Ŀ��\n�� �ؽ�Ʈ Ȥ�� �÷��̾� ������Ʈ�� Ŭ���ϸ� �޽����ڽ� ���";
    if (playermove->triggered) temp << " (�浹��)";
    temp << "\n�÷��̾� ��ǥ: ���� (" << wpos.x << ", " << wpos.y << ", " << wpos.z << ") / ȭ�� (" << spos.x << ", " << spos.y << ")";

    text->text = temp.str();
}

void TopText::OnMouseClick()
{
    MessageBox(NULL, "OnMouseClick() �����", "TopText", MB_OK);
}