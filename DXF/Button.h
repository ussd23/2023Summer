#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

//그냥 recttransform spriterenderer mousefunction 넣고 스크립트하나 만들어서 마우스기능함수 오버라이드에 콜백사용하면 버튼 아닌감...
//이 세개를 자동으로 컴포넌트로 등록하고 하위 오브젝트로 텍스트까지 넣게 만들면 되나
//아니면 저 세개 코드를 다 뜯어다가 버튼에 새로 만들어야하나

class SpriteRenderer;
class MouseFunction;

class Button : public Component
{
private:
	SpriteRenderer* spr;
	MouseFunction* mouse;

public:
	Button(string _texturename, DWORD _color, Vector2 _rectsize, Vector2 _rectindex);

	void OnMouseDown() override;
	void OnMouseUp() override;

	void Start() override;
};
