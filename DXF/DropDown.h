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
	//����ٿ� ��ũ��Ʈ���� ����ٿ�ɼǿ�����Ʈ �������, �ɼ��� �ݹ鿡 ����� ��� ���

public:
	void Start() override;

	void OnMouseDown() override;
	void OnMouseUp() override; 

	SerializeFunction(DropDown) {}
	DeserializeFunction() {}
};
