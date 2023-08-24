#include "Scripts.h"
#include <numeric>
#include <random>

void Minesweeper::Start() {
	InitGame(MapSize);
	IsStart = false;
}

void Minesweeper::Update() {

}

void Minesweeper::InitGame(int Size) {
	MapSize = Size;

	for (int i = Map.size() - 1; i >= Size * Size; i += -1) {
		GameObject::Destroy(Map[i]);
		Map.pop_back();
	}

	// 이전 칸 크기가 새로운 칸 보다 작으면 칸 추가
	for (int i = Map.size(); i < Size * Size; i += 1) {
		float Image_Size = 1;
		float Image_Between = 0.1;

		// 칸 생성
		GameObject* Mine_Obj = new PlaneObject("Mine", Vector3(0, 0, 0), "Mine.png");

		vector<Vertex> Mine_Vertex_Vector;
		Mine_Vertex_Vector.push_back({ -Image_Size / 2, 0.0f, -Image_Size / 2, 0xffffffff, 0.0f, 1.0f });
		Mine_Vertex_Vector.push_back({ -Image_Size / 2, 0.0f,  Image_Size / 2, 0xffffffff, 0.0f, 0.0f });
		Mine_Vertex_Vector.push_back({ Image_Size / 2, 0.0f, -Image_Size / 2, 0xffffffff, 1.0f, 1.0f });
		Mine_Vertex_Vector.push_back({ Image_Size / 2, 0.0f,  Image_Size / 2, 0xffffffff, 1.0f, 0.0f });
		VerticeRenderer* Mine_Vertex = GetComponentFromObject(Mine_Obj, VerticeRenderer);
		Mine_Vertex->m_RectSize = Vector2(13, 1);
		Mine_Vertex->m_RectIndex = Vector2(0, 0);
		Mine_Vertex->ChangeVertices(Mine_Vertex_Vector);
		Animator* Mine_Animator = new Animator(0, MAXINT, 100000000.f, true);
		AddComponentToObject(Mine_Obj, Mine_Animator);

		BoxCollider* Mine_Box = new BoxCollider(Vector3(0.8f, 0.8f, 0.8f), true);
		AddComponentToObject(Mine_Obj, Mine_Box);
		Mine* Mine_Info = new Mine();
		AddComponentToObject(Mine_Obj, Mine_Info);
		MouseFunction* Mine_Mouse = new MouseFunction();
		AddComponentToObject(Mine_Obj, Mine_Mouse);

		Map.push_back(Mine_Obj);
	}

	// 칸 초기화
	for (int i = 0; i < Map.size(); i += 1) {
		Mine* Mine_Info = GetComponentFromObject(Map[i], Mine);
		Mine_Info->InitMine(this, i);
	}

	IsStart = false;
	IsFinish = false;
	FindMine = 0;
	SetMine = 0;
}

void Minesweeper::StartGame(Mine* Start, int Count) {
	int MaxCount = min(Count, (int)Map.size() - 9);
	SetMine = MaxCount;

	std::random_device RNG;
	std::mt19937 RNG_Gen(RNG());
	std::vector<int> RNG_Range(Map.size(), 0);
	std::vector<int> RNG_Exclud;
	std::iota(RNG_Range.begin(), RNG_Range.end(), 1);

	// 시작 지점은 무조건 지뢰 없게하기
	for (int i = 0; i < 9; i += 1) {
		// 예외처리
		if (Start->GetMinePoint() % MapSize == 0) {
			if ((i == 0) || (i == 3) || (i == 6)) {
				continue;
			}
		}
		else if (Start->GetMinePoint() % MapSize == MapSize - 1) {
			if ((i == 2) || (i == 5) || (i == 8)) {
				continue;
			}
		}

		// 시작 칸 지점 등록
		int tPos = Start->GetMinePoint() + (((int)(i / 3) - 1) * MapSize) + ((i % 3) - 1);
		if (tPos >= 0 && tPos < Map.size()) {
			RNG_Exclud.push_back(tPos + 1);
		}
	}
	//RNG_Exclud.push_back(Start->GetMinePoint() + 1);

	// 전체칸에서 시작 칸 지점 제외
	for (int num : RNG_Exclud) {
		RNG_Range.erase(std::remove(RNG_Range.begin(), RNG_Range.end(), num), RNG_Range.end());
	}
	// 전체칸 무작위
	std::shuffle(RNG_Range.begin(), RNG_Range.end(), RNG_Gen);
	// 설정된 지뢰갯수만큼 반환
	RNG_Range.resize(min(MaxCount, (int)RNG_Range.size()));
	// 지뢰칸 설정
	for (int num : RNG_Range) {
		//Map[num - 1]->SetMine(true);
		Mine* Mine_Info = GetComponentFromObject(Map[num - 1], Mine);
		Mine_Info->SetMine(true);
	}


	// 모든 칸에 주변 지뢰 갯수 설정
	for (GameObject* Obj : Map) {
		Mine* tMine = GetComponentFromObject(Obj, Mine);
		if (tMine->GetMine() == true) {
			// 해당 칸에서 왼쪽위 칸부터 오른쪽아래 칸까지 반복
			for (int i = 0; i < 9; i += 1) {
				// 예외 처리
				if (i == 4) {
					continue;
				}
				if (tMine->GetMinePoint() % MapSize == 0) {
					if ((i == 0) || (i == 3) || (i == 6)) {
						continue;
					}
				}
				else if (tMine->GetMinePoint() % MapSize == MapSize - 1) {
					if ((i == 2) || (i == 5) || (i == 8)) {
						continue;
					}
				}

				int tPos = tMine->GetMinePoint() - (((int)(i / 3) - 1) * MapSize) + ((i % 3) - 1);
				// 주변칸이 올바른 값이면 근방 지뢰 갯수 설정
				if (tPos >= 0 && tPos < Map.size()) {
					//Map[tPos]->AddNearMine();
					Mine* Mine_Info = GetComponentFromObject(Map[tPos], Mine);
					Mine_Info->AddNearMine();
				}
			}
		}
	}
}

void Minesweeper::FinishGame(bool Clear) {
	// 게임 종료될때
	if (IsFinish == false) {
		IsFinish = true;
		for (GameObject* Obj : Map) {
			Mine* tMine = GetComponentFromObject(Obj, Mine);
			tMine->ShowMine();
		}

		if (Clear == true) {
			MessageBox(NULL, "GameClear", "MineSweeper", MB_OK);
		}
		else {
			MessageBox(NULL, "GameOver", "MineSweeper", MB_OK);
		}
	}
}

bool Minesweeper::GetStart() {
	return IsStart;
}

void Minesweeper::SetStart(bool Start) {
	IsStart = Start;
}

bool Minesweeper::GetFinish() {
	return IsFinish;
}

void Minesweeper::AddFind() {
	FindMine += 1;
	if (FindMine >= Map.size() - SetMine) {
		FinishGame(true);
	}
}

int Minesweeper::GetMapSize() {
	return MapSize;
}

int Minesweeper::GetMineCount() {
	return SetMine;
}

std::vector<GameObject*> Minesweeper::GetMap() {
	return Map;
}
