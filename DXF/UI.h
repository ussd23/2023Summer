#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"


class RectTransform;
class MouseFunction;
class TextRenderer;
class SpriteRenderer;

//toptext�� �������� ���� ����
class UI : public Component
{

};


//ui�� gameobject�� ������Ʈ�� ����ؼ� ����ϵ��� �ϰ�
//����Ҷ� �����ڿ� text, button, image, editbox �Է¹޾Ƽ� �׿� ���� ��� ����

//Ȥ�� ui���� ������Ʈ�� ui��� ��ø� �ϰ� ��ư�̴� ���� �ϴ°� ���� ������Ʈȭ

//�� ui �Ѱ��� ���� �������ϱ� ���� ������Ʈ�� ����� ���߿� �ʿ��ϴ� ������ �Ѱ� ����°ɷ�
//

/*
// Button
gameObject = new GameObject("btn1");
RectTransform* rect = new RectTransform(Vector2(300, 55), Vector3(0.f, 0.f, 0.f), Vector2(1.f, 1.f), Vector2(600, 110));
AddComponentToObject(gameObject, rect);
UI* ui = new UI("button");
AddComponentToObject(gameObject, ui);
mouse = new MouseFunction();
AddComponentToObject(gameObject, mouse);
AddObjectToScene(gameObject, g_RootTransform, transform);
*/
