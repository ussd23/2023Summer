#include "Scripts.h"

Mine::Mine(GameObject* Obj) {
	Mine_Object = Obj;
}

void Mine::Start() {

}

void Mine::Update() {

}

void Mine::OnMouseDown() {
	// 첫번째 칸 누르면 시작하기
	if (Mine_Sweeper->GetStart() == false) {
		Mine_Sweeper->SetStart(true);
		//MessageBox(NULL, "GameStart", "MineSweeper", MB_OK);

		// 게임시작 초기화
		Mine_Sweeper->StartGame(this, 20);
	}
	
	// 미공개 칸일시
	if (Mine_Show == false) {
		// 좌클릭시
		if (true) {
			// 깃발있으면 무시
			if (Mine_Flag == false) {
				// 지뢰면 종료
				if (Mine_Check == true) {
					Mine_Sweeper->FinishGame(false);
				}
				else {
					ShowMine();
				}
				//MessageBox(NULL, to_string(Mine_Point).c_str(), "MineMouseDown", MB_OK);
			}
		}
		// 우클릭시
		else {
			// 깃발 표시
			if (Mine_Flag == true) {
				Mine_Flag = false;
				VerticeRenderer* Mine_Vertex = GetComponentFromObject(Mine_Object, VerticeRenderer);
				Mine_Vertex->m_RectIndex = Vector2(0, 0);
			}
			else {
				Mine_Flag = true;
				VerticeRenderer* Mine_Vertex = GetComponentFromObject(Mine_Object, VerticeRenderer);
				Mine_Vertex->m_RectIndex = Vector2(11, 0);
			}
		}
	}
}

void Mine::InitMine(Minesweeper* Manager, int Index) {
	// 칸 초기화
	Mine_Sweeper = Manager;
	Mine_Point = Index;
	//Mine_Point = Mine_Sweeper->GetMap().size();
	
	Mine_Check = false;
	Mine_Near = 0;
	Mine_Show = false;
	Mine_Flag = false;

	VerticeRenderer* Mine_Vertex = GetComponentFromObject(Mine_Object, VerticeRenderer);
	Mine_Vertex->m_RectIndex = Vector2(0, 0);
}

void Mine::SetMine(bool Mine) {
	Mine_Check = Mine;
	Mine_Near = 0;
}

bool Mine::GetMine() {
	return Mine_Check;
}

int Mine::GetMinePoint() {
	return Mine_Point;
}

void Mine::AddNearMine() {
	Mine_Near += 1;
}

int Mine::GetNearMine() {
	return Mine_Near;
}

void Mine::ShowMine() {
	// 보여주기
	if (Mine_Show == false) {
		Mine_Show = true;

		// 해당칸이 지뢰면
		if (Mine_Check == true) {
			//MessageBox(NULL, "Mine", to_string(Mine_Point).c_str(), MB_OK);
			VerticeRenderer* Mine_Vertex = GetComponentFromObject(Mine_Object, VerticeRenderer);
			Mine_Vertex->m_RectIndex = Vector2(12, 0);
		}
		// 해당칸이 지뢰가 아니면
		else {
			// 주변칸에 지뢰없으면 주변칸 밝히기
			if (Mine_Near == 0) {
				// 해당 칸에서 왼쪽위 칸부터 오른쪽아래 칸까지 반복
				for (int i = 0; i < 9; i += 1) {
					// 예외처리
					if (i == 4) {
						continue;
					}
					if (Mine_Point % Mine_Sweeper->GetMapSize() == 0) {
						if ((i == 0) || (i == 3) || (i == 6)) {
							continue;
						}
					}
					else if (Mine_Point % Mine_Sweeper->GetMapSize() == Mine_Sweeper->GetMapSize() - 1) {
						if ((i == 2) || (i == 5) || (i == 8)) {
							continue;
						}
					}

					
					int tPos = Mine_Point - (((int)(i / 3) - 1) * Mine_Sweeper->GetMapSize()) + ((i % 3) - 1);
					// 주변칸이 올바른 값이면 보여주기
					if (tPos >= 0 && tPos < Mine_Sweeper->GetMap().size()) {
						Mine* Mine_Info = GetComponentFromObject(Mine_Sweeper->GetMap()[tPos], Mine);
						Mine_Info->ShowMine();
					}
				}
			}

			// 해당칸 밝히기
			//MessageBox(NULL, to_string(Mine_Near).c_str(), to_string(Mine_Point).c_str(), MB_OK);
			VerticeRenderer* Mine_Vertex = GetComponentFromObject(Mine_Object, VerticeRenderer);
			Mine_Vertex->m_RectIndex = Vector2(Mine_Near + 1, 0);
			Mine_Sweeper->AddFind();
		}
	}
}
