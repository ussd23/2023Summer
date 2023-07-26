#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"


class RectTransform;
class MouseFunction;
class TextRenderer;
class SpriteRenderer;

//toptext는 가져오진 말고 참고만
class UI : public Component
{

};


//ui도 gameobject에 컴포넌트로 등록해서 사용하도록 하고
//등록할때 생성자에 text, button, image, editbox 입력받아서 그에 따른 기능 제한

//혹은 ui에는 오브젝트가 ui라는 명시만 하고 버튼이니 뭐니 하는건 따로 컴포넌트화

//걍 ui 총괄은 감이 안잡히니까 각각 컴포넌트나 만들고 나중에 필요하다 싶으면 총괄 만드는걸로
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
