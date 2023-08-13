#pragma once
#include "Component.h"
#include "DXHeader.h"

class Mine : public Component {
protected:
	GameObject* Mine_Object;
	class Minesweeper* Mine_Sweeper;
	int Mine_Point = 0;

	bool Mine_Check = false;
	int Mine_Near = 0;
	bool Mine_Show = false;
	bool Mine_Flag = false;

public:
	Mine(GameObject* Obj);

	void Start() override;
	void Update() override;
	void OnMouseDown() override;

	// ĭ �ʱ�ȭ
	void InitMine(class Minesweeper* Manager, int Index);
	// ���� ����
	void SetMine(bool Mine);
	// ���ڿ��� ��ȯ
	bool GetMine();

	// ĭ ��ġ ��ȯ
	int GetMinePoint();
	// �ֺ��� ���� ���� ����
	void AddNearMine();
	// �ֺ��� ���� ���� ��ȯ
	int GetNearMine();
	// ĭ ����
	void ShowMine();

	SerializeFunction(Mine) {}
	DeserializeFunction() {}
};