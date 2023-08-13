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

	// 칸 초기화
	void InitMine(class Minesweeper* Manager, int Index);
	// 지뢰 설정
	void SetMine(bool Mine);
	// 지뢰여부 반환
	bool GetMine();

	// 칸 위치 반환
	int GetMinePoint();
	// 주변의 지뢰 갯수 설정
	void AddNearMine();
	// 주변의 지뢰 갯수 반환
	int GetNearMine();
	// 칸 공개
	void ShowMine();

	SerializeFunction(Mine) {}
	DeserializeFunction() {}
};