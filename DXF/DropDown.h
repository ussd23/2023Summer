#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "StandardLibrary.h"

class SpriteRenderer;
class MouseFunction;

class DropDown : public Component
{
protected:
	bool								m_IsClicked = false;
	bool								m_IsDown = false;
	string								m_NormalTexture;
	string								m_DropTexture;
	SpriteRenderer*				m_Sprite;
	vector<DropDownOption> m_Options;
	//드랍다운 스크립트에서 드랍다운옵션오브젝트 복사생성, 옵션의 콜백에 사용할 펑션 등록

public:
	void Start() override;

	void OnMouseDown() override;
	void OnMouseUp() override; 

	SerializeFunction(DropDown) {}
	DeserializeFunction() {}
};
