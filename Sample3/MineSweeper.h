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

	// ���� �ʱ�ȭ
	void InitGame(int Size);
	// ���� ���� �ʱ�ȭ
	void StartGame(class Mine* Start, int Count);
	// ���� ����
	void FinishGame(bool Clear);
	
	// ���� ���� ��ȯ
	bool GetStart();
	// ���� ����
	void SetStart(bool Start);
	// ���� ���� ��ȯ
	bool GetFinish();
	// ĭ ������ ����
	void AddFind();
	// ĭ ũ�� ��ȯ
	int GetMapSize();
	// ���� ���� ��ȯ
	int GetMineCount();
	// ĭ ��ȯ
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

