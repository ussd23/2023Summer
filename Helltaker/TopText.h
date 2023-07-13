//-----------------------------------------------------------------------------
// File: TopText
//
// Desc: 화면 상단에 텍스트를 출력하기 위한 스크립트
//
//		[Variables]
//		- text: 오브젝트의 TextRenderer 컴포넌트
//		- camera: 카메라 오브젝트의 Camera 컴포넌트
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"

class GameObject;
class TextRenderer;
class Camera;

class TopText : public Component
{
protected:
	TextRenderer*		text;
	Camera*				camera;

public:
	void Start() override;
	void Update() override;

	void OnMouseDown() override;
};

