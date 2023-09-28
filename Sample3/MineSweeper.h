#pragma once
#include "Component.h"
#include "DXHeader.h"
#include "Mine.h"
#include <random>

class Minesweeper : public Component {
protected:
	int MapSize = 5;
	std::vector<class GameObject*> Map;

	bool IsStart = false;
	bool IsFinish = false;
	int FindMine = 0;
	int SetMine = 0;
public:
	void Start() override;
	void Update() override;

	// 게임 초기화
	void InitGame(int Size);
	// 게임 시작 초기화
	void StartGame(class Mine* Start, int Count);
	// 게임 종료
	void FinishGame(bool Clear);
	
	// 시작 여부 반환
	bool GetStart();
	// 시작 설정
	void SetStart(bool Start);
	// 종료 여부 반환
	bool GetFinish();
	// 칸 공개수 증가
	void AddFind();
	// 칸 크기 반환
	int GetMapSize();
	// 지뢰 갯수 반환
	int GetMineCount();
	// 칸 반환
	std::vector<class GameObject*> GetMap();

	SerializeFunction(Minesweeper)
	{
		if (!IsStart || !p_Mode) return;

		vector<string> cheat;

		for (int i = 0; i < MapSize; ++i)
		{
			stringstream ss;
			for (int j = 0; j < MapSize; ++j)
			{
				Mine* mine = GetComponentFromObject(Map[i * MapSize + j], Mine);
				ss << mine->GetMine() << " ";
			}
			cheat.push_back(ss.str());
		}
		VectorSerialize(cheat);
	}
};

