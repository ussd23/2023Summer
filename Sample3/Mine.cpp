#include "Scripts.h"

Mine::Mine(GameObject* Obj) {
	Mine_Object = Obj;
}

void Mine::Start() {

}

void Mine::Update() {

}

void Mine::OnMouseDown() {
	// ù��° ĭ ������ �����ϱ�
	if (Mine_Sweeper->GetStart() == false) {
		Mine_Sweeper->SetStart(true);
		//MessageBox(NULL, "GameStart", "MineSweeper", MB_OK);

		// ���ӽ��� �ʱ�ȭ
		Mine_Sweeper->StartGame(this, 20);
	}
	
	// �̰��� ĭ�Ͻ�
	if (Mine_Show == false) {
		// ��Ŭ����
		if (true) {
			// ��������� ����
			if (Mine_Flag == false) {
				// ���ڸ� ����
				if (Mine_Check == true) {
					Mine_Sweeper->FinishGame(false);
				}
				else {
					ShowMine();
				}
				//MessageBox(NULL, to_string(Mine_Point).c_str(), "MineMouseDown", MB_OK);
			}
		}
		// ��Ŭ����
		else {
			// ��� ǥ��
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
	// ĭ �ʱ�ȭ
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
	// �����ֱ�
	if (Mine_Show == false) {
		Mine_Show = true;

		// �ش�ĭ�� ���ڸ�
		if (Mine_Check == true) {
			//MessageBox(NULL, "Mine", to_string(Mine_Point).c_str(), MB_OK);
			VerticeRenderer* Mine_Vertex = GetComponentFromObject(Mine_Object, VerticeRenderer);
			Mine_Vertex->m_RectIndex = Vector2(12, 0);
		}
		// �ش�ĭ�� ���ڰ� �ƴϸ�
		else {
			// �ֺ�ĭ�� ���ھ����� �ֺ�ĭ ������
			if (Mine_Near == 0) {
				// �ش� ĭ���� ������ ĭ���� �����ʾƷ� ĭ���� �ݺ�
				for (int i = 0; i < 9; i += 1) {
					// ����ó��
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
					// �ֺ�ĭ�� �ùٸ� ���̸� �����ֱ�
					if (tPos >= 0 && tPos < Mine_Sweeper->GetMap().size()) {
						Mine* Mine_Info = GetComponentFromObject(Mine_Sweeper->GetMap()[tPos], Mine);
						Mine_Info->ShowMine();
					}
				}
			}

			// �ش�ĭ ������
			//MessageBox(NULL, to_string(Mine_Near).c_str(), to_string(Mine_Point).c_str(), MB_OK);
			VerticeRenderer* Mine_Vertex = GetComponentFromObject(Mine_Object, VerticeRenderer);
			Mine_Vertex->m_RectIndex = Vector2(Mine_Near + 1, 0);
			Mine_Sweeper->AddFind();
		}
	}
}
