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

        //���⼭ temp�� xy�� ����
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
        //�׸��� ���缭 ��ġ
        Transform* trans = GetComponentFromObject(_collider->gameObject, Transform);
        Bubble* colbubble = GetComponentFromObject(_collider->gameObject, Bubble);
        BubbleManager* bubman = GetComponentFromObject(m_BubbleManager, BubbleManager);

        if (trans == nullptr) return; 
        if (colbubble == nullptr) return;
        if (bubman == nullptr) return;

        Vector3 collpos = trans->GetPosition();
        Vector3 thispos = m_Transform->GetPosition();

        //y��ǥ ��ġ ����
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
        //x��ǥ ��ġ ����
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

        //���ӿ���
        if (m_PosInManager.y == 8)
        {
            MessageBox(NULL, "�ƽ��׿�", "���ӿ���", MB_OK);
            m_GameOver = true;
            Controll::m_Controll->m_GameOver = true;
            return;
        }

        //����Ŵ����� m_AllBubble�� �浹������ ��� ��ġ�� ������ �ڱ� �ڽ��� �߰�
        bubman->m_AllBubble[m_PosInManager.y][m_PosInManager.x] = this;

        //�߰� ��ġ�� ������� m_NearSameBubbles�� ������ �߰�
        SetNearSameBubbles();

        //m_NearSameBubbles�� ������� ���� �Լ��� ȣ���� ����� m_NearSameBubbles���� �ڽ��� �߰��ɼ� �ְ� ��
        for (int i = 0; i < m_NearSameBubbles.size(); i++)
        {
            m_NearSameBubbles[i]->AddBubble(this);
        }

        //����� ���� Ȯ��
        //result�� m_NearSameBubbles�� �����͸� �����ϰ� �ڱ��ڽ��� �߰�
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
            //�ڽŰ� ����� �ڽŰ� ���� ���� ������ ��� ã�� �޾ƿ�
            result = m_NearSameBubbles[i]->FindBubbles(result);
        }

        //����� ���� ������ 3�� �̸��ϰ�� �� ������ �ٸ� ������ ������ ����
        if (result.size() < 3)
        {
            coll = GetComponentFromObject(gameObject, SphereCollider);

            if (coll == nullptr) return;

            coll->m_isPassive = true;

            m_isBullet = false;
        }
        //3�� �̻��̸� ��� �ı�
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
            //���� źȯ ����
            GameObj = new MeshObject("bubble", Vector3(0, -6.1, -8), "PuzzleBobble\\red.x");
            scollider = new SphereCollider(1.1f);
            AddComponentToObject(GameObj, scollider);
            bubble = new Bubble(1);
            AddComponentToObject(GameObj, bubble);
            bubble->m_isBullet = true;
            break;
        case 2:
            //���� źȯ ����
            GameObj = new MeshObject("bubble", Vector3(0, -6.1, -8), "PuzzleBobble\\green.x");
            scollider = new SphereCollider(1.1f);
            AddComponentToObject(GameObj, scollider);
            bubble = new Bubble(2);
            AddComponentToObject(GameObj, bubble);
            bubble->m_isBullet = true;
            break;
        case 3:
            //���� źȯ ����
            GameObj = new MeshObject("bubble", Vector3(0, -6.1, -8), "PuzzleBobble\\blue.x");
            scollider = new SphereCollider(1.1f);
            AddComponentToObject(GameObj, scollider);
            bubble = new Bubble(3);
            AddComponentToObject(GameObj, bubble);
            bubble->m_isBullet = true;
            break;
        case 4:
            //���� źȯ ����
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

    //Ȯ�οϷ� ��� ����
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

        //������������ ����� Ȯ�� �Ϸ��Ͽ� �����Ե� ����� ������� ȣ���� ��ϰ� Ȯ�οϷ� ��Ͽ� �߰�
        if (add == true)
        {
            target.push_back(m_NearSameBubbles[i]);
            checked.push_back(m_NearSameBubbles[i]);
        }
    }

    //ȣ���� ��Ͽ� ���Ե� ��󿡰� Ȯ�οϷ� ����� ���ڷ� �Ѱܼ� �Լ� ����
    for (int i = 0; i < target.size(); i++)
    {
        //����� ���� ������� Ȯ�οϷ� ��� ����
        checked = target[i]->FindBubbles(checked);
    }

    //Ȯ�οϷ� ��� ��ȯ
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
