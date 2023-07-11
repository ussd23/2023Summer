#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"


class MouseFunction;

//toptext는 가져오진 말고 참고만
class UI : public Component
{
};


/*
// Button
gameObject = new GameObject("btn1");
RectTransform* rect = new RectTransform(Vector2(300, 55), Vector3(0.f, 0.f, 0.f), Vector2(1.f, 1.f), Vector2(600, 110));
AddComponentToObject(gameObject, rect);
UI* ui = new UI("button");
AddComponentToObject(gameObject, ui);
PlayerMove* pmove = new PlayerMove(20.f);
AddComponentToObject(gameObject, pmove);
SphereCollider* scollider = new SphereCollider(1.0f);
AddComponentToObject(gameObject, scollider);
mouse = new MouseFunction();
AddComponentToObject(gameObject, mouse);
AddObjectToScene(gameObject, g_RootTransform, transform);
*/
