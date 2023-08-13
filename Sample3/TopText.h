//-----------------------------------------------------------------------------
// File: TopText
//
// Desc: 화면 상단에 텍스트를 출력하기 위한 스크립트
//
//		[Variables]
//		- m_Text 오브젝트의 TextRenderer 컴포넌트
//		- m_Camera: 카메라 오브젝트의 Camera 컴포넌트
//-----------------------------------------------------------------------------

#pragma once
#include "Component.h"

class GameObject;
class TextRenderer;
class Camera;

class TopText : public Component
{
protected:
	TextRenderer*		m_Text;

public:
	void Start() override;
	void Update() override;

	SerializeFunction(TopText) {}
	DeserializeFunction() {}
};

