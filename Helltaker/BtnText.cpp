#include "Scripts.h"

void BtnText::Start()
{
    text = GetComponentFromObject(gameObject, TextRenderer);
}

void BtnText::Update()
{
    if (text == nullptr) return;

    stringstream temp;
    //temp << fixed << setprecision(2) << "[FPS: " << Time::framePerSec << " / AvgFPS: " << Time::avgFrame << "]\n"\
    //    << "W/A/S/D: �̵�, Q/E: ȸ��, R/F: Ȯ��/���\n[" << (camera->fovRate * 100)\
    //    << "%] ���콺 ��: ����/�ܾƿ�, ��Ŭ��: ī�޶� ��Ŀ��\n�� �ؽ�Ʈ Ȥ�� �÷��̾� ������Ʈ�� Ŭ���ϸ� �޽����ڽ� ���";
    temp << "BtnText";

    text->text = temp.str();
}