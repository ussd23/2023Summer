#include "Scripts.h"

Bubble::Bubble(int p_Code)
{
    m_Code = p_Code;
}

void Bubble::Start()
{
    m_Transform = GetComponentFromObject(gameObject, Transform);
    m_Controll = Controll::m_Controll->gameObject;
    m_BubbleManager = BubbleManager::m_BubbleManager->gameObject;
    m_Speed = 15;
    if(!m_isBullet) SetNearSameBubbles();
}

void Bubble::Update()
{
    if (m_isBullet == true && !m_GameOver)
    {
        Vector3 position = m_Transform->GetPosition();

        float length;

        //여기서 temp의 xy값 설정
        if (GetInputBuffer(Input::Key, VK_SPACE)) 
        {
            RectTransform* controllrect = GetComponentFromObject(m_Controll, RectTransform);
            Vector3 rotation = Functions::QuaternionToEuler(controllrect->GetRotation());

            // convert an angle to x/yu
            m_Mover.x = sin(rotation.z / 90 * D3DX_PI * 0.5) * m_Speed;
            m_Mover.y = cos(rotation.z / 90 * D3DX_PI * 0.5) * m_Speed;
        }
        
        length = sqrt((fabs(m_Mover.x) * fabs(m_Mover.x) + fabs(m_Mover.y) * fabs(m_Mover.y)));
        if (length > 0.f)
        {
            position.x += (m_Mover.x / length) * Time::deltaTime * m_Speed;
            position.y += (m_Mover.y / length) * Time::deltaTime * m_Speed;

            if (position.x + 1 > 8)
            {
                position.x = 7;
                m_Mover.x *= -1;
            }
            if (position.x - 1 < -8)
            {
                position.x = -7;
                m_Mover.x *= -1;
            }
        }

        m_Transform->SetPosition(position);
    }
}

void Bubble::OnTriggerEnter(Collider* _collider)
{
    if (m_isBullet)
    {
        //그리드 맞춰서 배치
        Transform* trans = GetComponentFromObject(_collider->gameObject, Transform);
        Bubble* colbubble = GetComponentFromObject(_collider->gameObject, Bubble);
        BubbleManager* bubman = GetComponentFromObject(m_BubbleManager, BubbleManager);

        if (trans == nullptr) return; 
        if (colbubble == nullptr) return;
        if (bubman == nullptr) return;

        Vector3 collpos = trans->GetPosition();
        Vector3 thispos = m_Transform->GetPosition();

        //y좌표 위치 설정
        if (collpos.y >= thispos.y + 1)
        {
            thispos.y = collpos.y - 1.9;
            m_PosInManager.y = colbubble->m_PosInManager.y + 1;
        }
        else if (collpos.y <= thispos.y - 1)
        {
            thispos.y = collpos.y + 1.9;
            m_PosInManager.y = colbubble->m_PosInManager.y - 1;
        }
        else
        {
            thispos.y = collpos.y;
            m_PosInManager.y = colbubble->m_PosInManager.y;
        }
        //x좌표 위치 설정
        if (collpos.x >= thispos.x)
        {
            if (colbubble->m_PosInManager.y % 2 == 0)
            {
                if (m_PosInManager.y == colbubble->m_PosInManager.y)
                {
                    thispos.x = collpos.x - 2.05;
                    m_PosInManager.x = colbubble->m_PosInManager.x - 1;
                }
                else
                {
                    thispos.x = collpos.x - 1.05;
                    m_PosInManager.x = colbubble->m_PosInManager.x - 1;
                }
            }
            else
            {
                if (m_PosInManager.y == colbubble->m_PosInManager.y)
                {
                    thispos.x = collpos.x - 2.05;
                    m_PosInManager.x = colbubble->m_PosInManager.x - 1;
                }
                else
                {
                    thispos.x = collpos.x - 1.05;
                    m_PosInManager.x = colbubble->m_PosInManager.x;
                }
            }
        }
        else
        {
            if (colbubble->m_PosInManager.y % 2 == 1)
            {
                if (m_PosInManager.y == colbubble->m_PosInManager.y)
                {
                    thispos.x = collpos.x + 2.05;
                    m_PosInManager.x = colbubble->m_PosInManager.x + 1;
                }
                else
                {
                    thispos.x = collpos.x + 1.05;
                    m_PosInManager.x = colbubble->m_PosInManager.x + 1;
                }
            }
            else
            {
                if (m_PosInManager.y == colbubble->m_PosInManager.y)
                {
                    thispos.x = collpos.x + 2.05;
                    m_PosInManager.x = colbubble->m_PosInManager.x + 1;
                }
                else
                {
                    thispos.x = collpos.x + 1.05;
                    m_PosInManager.x = colbubble->m_PosInManager.x;
                }
            }
        }

        m_Transform->SetPosition(thispos);

        //게임오버
        if (m_PosInManager.y == 8)
        {
            MessageBox(NULL, "아쉽네요", "게임오버", MB_OK);
            m_GameOver = true;
            Controll::m_Controll->m_GameOver = true;
            return;
        }

        //버블매니저의 m_AllBubble에 충돌대상과의 상대 위치를 따져서 자기 자신을 추가
        bubman->m_AllBubble[m_PosInManager.y][m_PosInManager.x] = this;

        //추가 위치를 기반으로 m_NearSameBubbles에 데이터 추가
        SetNearSameBubbles();

        //m_NearSameBubbles의 버블들이 가진 함수를 호출해 대상의 m_NearSameBubbles에도 자신이 추가될수 있게 함
        for (int i = 0; i < m_NearSameBubbles.size(); i++)
        {
            m_NearSameBubbles[i]->AddBubble(this);
        }

        //연결된 버블 확인
        //result에 m_NearSameBubbles의 데이터를 복사하고 자기자신을 추가
        vector<Bubble*> result;
        SphereCollider* coll;
        GameObject* destroyobj;

        for (int i = 0; i < m_NearSameBubbles.size(); i++)
        {
            result.push_back(m_NearSameBubbles[i]);
        }
        result.push_back(this);

        for (int i = 0; i < m_NearSameBubbles.size(); i++)
        {
            //자신과 연결된 자신과 색이 같은 버블을 모두 찾아 받아옴
            result = m_NearSameBubbles[i]->FindBubbles(result);
        }

        //연결된 같은 버블이 3개 미만일경우 이 버블을 다른 버블들과 같도록 설정
        if (result.size() < 3)
        {
            coll = GetComponentFromObject(gameObject, SphereCollider);

            if (coll == nullptr) return;

            coll->m_isPassive = true;

            m_isBullet = false;
        }
        //3개 이상이면 모두 파괴
        else
        {
            for (int i = 0; i < result.size(); i++)
            {
                destroyobj = result[i]->gameObject;

                GameObject::Destroy(destroyobj);
            }
        }

        int collor = (rand() % 4) + 1;
        GameObject* GameObj;
        SphereCollider* scollider;
        Bubble* bubble;

        switch (collor)
        {
        case 1:
            //다음 탄환 생성
            GameObj = new MeshObject("bubble", Vector3(0, -6.1, -8), "PuzzleBobble\\red.x");
            scollider = new SphereCollider(1.1f);
            AddComponentToObject(GameObj, scollider);
            bubble = new Bubble(1);
            AddComponentToObject(GameObj, bubble);
            bubble->m_isBullet = true;
            break;
        case 2:
            //다음 탄환 생성
            GameObj = new MeshObject("bubble", Vector3(0, -6.1, -8), "PuzzleBobble\\green.x");
            scollider = new SphereCollider(1.1f);
            AddComponentToObject(GameObj, scollider);
            bubble = new Bubble(2);
            AddComponentToObject(GameObj, bubble);
            bubble->m_isBullet = true;
            break;
        case 3:
            //다음 탄환 생성
            GameObj = new MeshObject("bubble", Vector3(0, -6.1, -8), "PuzzleBobble\\blue.x");
            scollider = new SphereCollider(1.1f);
            AddComponentToObject(GameObj, scollider);
            bubble = new Bubble(3);
            AddComponentToObject(GameObj, bubble);
            bubble->m_isBullet = true;
            break;
        case 4:
            //다음 탄환 생성
            GameObj = new MeshObject("bubble", Vector3(0, -6.1, -8), "PuzzleBobble\\yellow.x");
            scollider = new SphereCollider(1.1f);
            AddComponentToObject(GameObj, scollider);
            bubble = new Bubble(4);
            AddComponentToObject(GameObj, bubble);
            bubble->m_isBullet = true;
            break;
        }
    }
}

void Bubble::SetPosInManager(int x, int y)
{
    m_PosInManager.x = x;
    m_PosInManager.y = y;
}

void Bubble::SetNearSameBubbles()
{
    BubbleManager* bubman = GetComponentFromObject(m_BubbleManager, BubbleManager);

    if (bubman == nullptr) return;

    if (m_PosInManager.y % 2 == 0)
    {
        if (m_PosInManager.y != 0)
        {
            if (m_PosInManager.x != 0)
            {
                if (bubman->m_AllBubble[m_PosInManager.y - 1][m_PosInManager.x - 1] != nullptr
                    && bubman->m_AllBubble[m_PosInManager.y - 1][m_PosInManager.x - 1]->GetCode() == m_Code) AddBubble(bubman->m_AllBubble[m_PosInManager.y - 1][m_PosInManager.x - 1]);
            }
            if (bubman->m_AllBubble[m_PosInManager.y - 1][m_PosInManager.x] != nullptr
                && bubman->m_AllBubble[m_PosInManager.y - 1][m_PosInManager.x]->GetCode() == m_Code) AddBubble(bubman->m_AllBubble[m_PosInManager.y - 1][m_PosInManager.x]);
        }
        if (m_PosInManager.x != 0)
        {
            if (bubman->m_AllBubble[m_PosInManager.y][m_PosInManager.x - 1] != nullptr
                && bubman->m_AllBubble[m_PosInManager.y][m_PosInManager.x - 1]->GetCode() == m_Code) AddBubble(bubman->m_AllBubble[m_PosInManager.y][m_PosInManager.x - 1]);
        }
        if (m_PosInManager.x != 7)
        {
            if (bubman->m_AllBubble[m_PosInManager.y][m_PosInManager.x + 1] != nullptr
                && bubman->m_AllBubble[m_PosInManager.y][m_PosInManager.x + 1]->GetCode() == m_Code) AddBubble(bubman->m_AllBubble[m_PosInManager.y][m_PosInManager.x + 1]);
        }
        if (m_PosInManager.y != 6)
        {
            if (m_PosInManager.x != 0)
            {
                if (bubman->m_AllBubble[m_PosInManager.y + 1][m_PosInManager.x - 1] != nullptr
                    && bubman->m_AllBubble[m_PosInManager.y + 1][m_PosInManager.x - 1]->GetCode() == m_Code) AddBubble(bubman->m_AllBubble[m_PosInManager.y + 1][m_PosInManager.x - 1]);
            }
            if (bubman->m_AllBubble[m_PosInManager.y + 1][m_PosInManager.x] != nullptr
                && bubman->m_AllBubble[m_PosInManager.y + 1][m_PosInManager.x]->GetCode() == m_Code) AddBubble(bubman->m_AllBubble[m_PosInManager.y + 1][m_PosInManager.x]);
        }
    }
    else
    {
        if (m_PosInManager.y != 0)
        {
            if (m_PosInManager.x != 7)
            {
                if (bubman->m_AllBubble[m_PosInManager.y - 1][m_PosInManager.x + 1] != nullptr
                    && bubman->m_AllBubble[m_PosInManager.y - 1][m_PosInManager.x + 1]->GetCode() == m_Code) AddBubble(bubman->m_AllBubble[m_PosInManager.y - 1][m_PosInManager.x + 1]);
            }
            if (bubman->m_AllBubble[m_PosInManager.y - 1][m_PosInManager.x] != nullptr
                && bubman->m_AllBubble[m_PosInManager.y - 1][m_PosInManager.x]->GetCode() == m_Code) AddBubble(bubman->m_AllBubble[m_PosInManager.y - 1][m_PosInManager.x]);
        }
        if (m_PosInManager.x != 0)
        {
            if (bubman->m_AllBubble[m_PosInManager.y][m_PosInManager.x - 1] != nullptr
                && bubman->m_AllBubble[m_PosInManager.y][m_PosInManager.x - 1]->GetCode() == m_Code) AddBubble(bubman->m_AllBubble[m_PosInManager.y][m_PosInManager.x - 1]);
        }
        if (m_PosInManager.x != 7)
        {
            if (bubman->m_AllBubble[m_PosInManager.y][m_PosInManager.x + 1] != nullptr
                && bubman->m_AllBubble[m_PosInManager.y][m_PosInManager.x + 1]->GetCode() == m_Code) AddBubble(bubman->m_AllBubble[m_PosInManager.y][m_PosInManager.x + 1]);
        }
        if (m_PosInManager.y != 6)
        {
            if (m_PosInManager.x != 7)
            {
                if (bubman->m_AllBubble[m_PosInManager.y + 1][m_PosInManager.x + 1] != nullptr
                    && bubman->m_AllBubble[m_PosInManager.y + 1][m_PosInManager.x + 1]->GetCode() == m_Code) AddBubble(bubman->m_AllBubble[m_PosInManager.y + 1][m_PosInManager.x + 1]);
            }
            if (bubman->m_AllBubble[m_PosInManager.y + 1][m_PosInManager.x] != nullptr
                && bubman->m_AllBubble[m_PosInManager.y + 1][m_PosInManager.x]->GetCode() == m_Code) AddBubble(bubman->m_AllBubble[m_PosInManager.y + 1][m_PosInManager.x]);
        }
    }
}

vector<Bubble*> Bubble::FindBubbles(vector<Bubble*> p_Bubbles)
{
    bool add;
    vector<Bubble*> checked;
    vector<Bubble*> target;

    //확인완료 목록 복사
    //for (int i = 0; i < p_Bubbles.size(); i++)
    //{
    //    checked.push_back(p_Bubbles[i]);
    //}
    checked = p_Bubbles;

    for (int i = 0; i < m_NearSameBubbles.size(); i++)
    {
        add = true;
        for (int j = 0; j < p_Bubbles.size(); j++)
        {
            if (m_NearSameBubbles[i] == p_Bubbles[j])
            {
                add = false;
                break;
            }
        }

        //인접동종버블 목록중 확인 완료목록에 미포함된 대상이 있을경우 호출대상 목록과 확인완료 목록에 추가
        if (add == true)
        {
            target.push_back(m_NearSameBubbles[i]);
            checked.push_back(m_NearSameBubbles[i]);
        }
    }

    //호출대상 목록에 포함된 대상에게 확인완료 목록을 인자로 넘겨서 함수 실행
    for (int i = 0; i < target.size(); i++)
    {
        //결과로 받은 목록으로 확인완료 목록 갱신
        checked = target[i]->FindBubbles(checked);
    }

    //확인완료 목록 반환
    return checked;
}

void Bubble::AddBubble(Bubble* p_Bubble)
{
    if (p_Bubble->GetCode() == m_Code) m_NearSameBubbles.push_back(p_Bubble);
}

int Bubble::GetCode()
{
    return m_Code;
}
