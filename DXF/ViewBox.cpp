#include "ComponentHeader.h"

void ViewBox::Start()
{
    m_Rect = GetComponentFromObject(gameObject, RectTransform);

    //contentbox�� scroll���� ������Ʈ���� recttranceform���� �̸� �޾Ƶ�
    if (m_Rect != nullptr)
    {
        int cnt = m_Rect->GetChildCount();
        for (int i=0; i< cnt; i++)
        {
            RectTransform* ChildRect = m_Rect->GetChild(i);
            if (ChildRect->gameObject->m_Name.compare("contentbox") == 0)
            {
                m_ContentRect = ChildRect;
                ContentBox* tempcont = GetComponentFromObject(m_ContentRect->gameObject, ContentBox);
                tempcont->InitContPos();
            }
            else if (ChildRect->gameObject->m_Name.compare("VerticalScroll") == 0)
            {
                m_VScrollRect = ChildRect;
            }
            else if (ChildRect->gameObject->m_Name.compare("HorizontalScroll") == 0)
            {
                m_HScrollRect = ChildRect;
            }
        }

        if (m_VScrollRect != nullptr)
        {
            int cnt = m_VScrollRect->GetChildCount();
            for (int i = 0; i < cnt; i++)
            {
                RectTransform* ChildRect = m_VScrollRect->GetChild(i);
                if (ChildRect->gameObject->m_Name.compare("VerticalScrollBar") == 0)
                {
                    m_VScrollBarRect = ChildRect;
                }
            }
        }

        if (m_HScrollRect != nullptr)
        {
            int cnt = m_HScrollRect->GetChildCount();
            for (int i = 0; i < cnt; i++)
            {
                RectTransform* ChildRect = m_HScrollRect->GetChild(i);
                if (ChildRect->gameObject->m_Name.compare("HorizontalScrollBar") == 0)
                {
                    m_HScrollBarRect = ChildRect;
                }
            }
        }

        CalcContentMovableRange();
        AdjustScrollBarSize();
    }
}

void ViewBox::Update()
{
    if (m_isDown)
    {
        if (GetInputBuffer(Mouse, MouseInput::LBUTTONUP))
        {
            m_isDown = false;
            return;
        }

        MoveContentBox();

        //���콺 ��ġ ����
        m_MousePrePos = Input::MousePosition;
    }
}

void ViewBox::MoveContentBox()
{
    if (m_ContentRect == nullptr) return;

    Vector2 contPos = m_ContentRect->GetPosition();

    Vector2 normal = NormalizePosition(contPos, m_ContentMinRange, m_ContentMaxRange);

    //���� ���� �Ѱ迡 �����Ѱ�� �������θ� ������ �� �ְ� ��
    if (normal.x == 1)
    {
        if (Input::MousePosition.x < m_MousePrePos.x)
        {
            contPos.x = contPos.x + (Input::MousePosition.x - m_MousePrePos.x);
        }
    }
    //���� ���� �Ѱ迡 �����Ѱ�� ���������θ� ������ �� �ְ� ��
    else if (normal.x == 0)
    {
        if (Input::MousePosition.x > m_MousePrePos.x)
        {
            contPos.x = contPos.x + (Input::MousePosition.x - m_MousePrePos.x);
        }
    }
    //����ʵ� �ƴ϶�� �����Ӱ� ������ �� �ְ� ��
    else
    {
        contPos.x = contPos.x + (Input::MousePosition.x - m_MousePrePos.x);
    }

    //���� ���� �Ѱ迡 �����Ѱ�� �������θ� ������ �� �ְ� ��
    if (normal.y == 1)
    {
        if (Input::MousePosition.y < m_MousePrePos.y)
        {
            contPos.y = contPos.y + (Input::MousePosition.y - m_MousePrePos.y);
        }
    }
    //���� ���� �Ѱ迡 �����Ѱ�� �Ʒ������θ� ������ �� �ְ� ��
    else if (normal.y == 0)
    {
        if (Input::MousePosition.y > m_MousePrePos.y)
        {
            contPos.y = contPos.y + (Input::MousePosition.y - m_MousePrePos.y);
        }

    }
    //����ʵ� �ƴ϶�� �����Ӱ� ������ �� �ְ� ��
    else
    {
        contPos.y = contPos.y + (Input::MousePosition.y - m_MousePrePos.y);
    }

    //������ ��ġ�� �ٽ� �ѹ� ����ȭ
    normal = NormalizePosition(contPos, m_ContentMinRange, m_ContentMaxRange);

    //������ ��ġ�� ���� ���� �Ѱ踦 ������ ��ġ�� �Ѱ�ġ�� ����
    if (normal.x > 1)
    {
        normal.x = 1;
    }
    //������ ��ġ�� ���� ���� �Ѱ踦 ������ ��ġ�� �Ѱ�ġ�� ����
    else if (normal.x < 0)
    {
        //�������ڽ� ���̰� 700 �̸��̸� ���������� �����̵��� ����
        if (m_ContentRect->m_Size.x < 700)
        {
            ExtendContentBoxSizeX();

            //�������ڽ� ũ�� ���� �������� �������ڽ��� ũ��� ��ġ�� �ٲ�Ƿ� ������ ��ġ�� ������������ �ٽ� �ѹ� ����ȭ
            contPos = m_ContentRect->GetPosition();

            normal = NormalizePosition(contPos, m_ContentMinRange, m_ContentMaxRange);
        }
        else
        {
            normal.x = 0;
        }
    }

    //������ ��ġ�� ���� ���� �Ѱ踦 ������ ��ġ�� �Ѱ�ġ�� ����
    if (normal.y > 1)
    {
        normal.y = 1;
    }
    //������ ��ġ�� ���� ���� �Ѱ踦 ������ ��ġ�� �Ѱ�ġ�� ����
    else if (normal.y < 0)
    {
        //�������ڽ� ���̰� 700 �̸��̸� �Ʒ��� �����̵��� ����
        if (m_ContentRect->m_Size.y < 700)
        {
            ExtendContentBoxSizeY();

            //�������ڽ� ũ�� ���� �������� �������ڽ��� ũ��� ��ġ�� �ٲ�Ƿ� ������ ��ġ�� ������������ �ٽ� �ѹ� ����ȭ
            contPos = m_ContentRect->GetPosition();

            normal = NormalizePosition(contPos, m_ContentMinRange, m_ContentMaxRange);
        }
        else
        {
            normal.y = 0;
        }
    }

    //���� ������ ��ġ�� �������ڽ��� ����
    Vector2 tempPos = DisNormalizePosition(normal, m_ContentMinRange, m_ContentMaxRange);
    m_ContentRect->SetPosition(tempPos);

    //�������ڽ��� ��ġ ���濡 ���� ��ũ�ѹ� ��ġ ����
    UpdateScrollBar();
}

//��ũ�ѹ��� ��ġ ���濡 ���� ������ �ڽ� ��ġ ����
void ViewBox::UpdateContentBox()
{
    Vector2 tempPos;

    if (m_ContentRect == nullptr) return;
    Vector2 contPos = m_ContentRect->GetPosition();

    if (m_VScrollBarRect != nullptr) 
    {
        Vector2 vscbPos = m_VScrollBarRect->GetPosition();
        tempPos.y = vscbPos.y;
    }
    else
    {
        tempPos.y = 0;
    }

    if (m_HScrollBarRect != nullptr) 
    {
        Vector2 hscbPos = m_HScrollBarRect->GetPosition();
        tempPos.x = hscbPos.x;
    }
    else
    {
        tempPos.x = 0;
    }

    Vector2 normal = NormalizePosition(tempPos, m_ScrollBarMinRange, m_ScrollBarMaxRange);
    normal.x = 1 - normal.x;
    normal.y = 1 - normal.y;

    tempPos = DisNormalizePosition(normal, m_ContentMinRange, m_ContentMaxRange);

    m_ContentRect->SetPosition(tempPos);
}

//�������ڽ��� ��ġ ���濡 ���� ��ũ�ѹ� ��ġ ����
void ViewBox::UpdateScrollBar()
{
    if (m_ContentRect == nullptr) return;
    Vector2 contPos = m_ContentRect->GetPosition();

    Vector2 normal = NormalizePosition(contPos, m_ContentMinRange, m_ContentMaxRange);
    normal.x = 1 - normal.x;
    normal.y = 1 - normal.y;

    Vector2 tempPos = DisNormalizePosition(normal, m_ScrollBarMinRange, m_ScrollBarMaxRange);

    if (m_VScrollBarRect != nullptr)
    {
        Vector2 vscbPos = m_VScrollBarRect->GetPosition();
        vscbPos.y = tempPos.y;
        m_VScrollBarRect->SetPosition(vscbPos);
    }

    if (m_HScrollBarRect != nullptr)
    {
        Vector2 hscbPos = m_HScrollBarRect->GetPosition();
        hscbPos.x = tempPos.x;
        m_HScrollBarRect->SetPosition(hscbPos);
    }
}

//��ũ�ѹ��� ���� ������ ����
void ViewBox::CalcScrollMovableRange()
{
    //���� ��ũ�ѹ� ����/���� ���
    //��ũ���� ����/�¿� �� ��ǥ���� ��ũ�ѹ� ����/���� ���ݸ�ŭ ���� = ��������
    if (m_VScrollBarRect != nullptr)
    {
        m_ScrollBarMaxRange.y = (m_VScrollRect->m_Size.y - m_VScrollBarRect->m_Size.y) * 0.5;
        m_ScrollBarMinRange.y = -(m_VScrollRect->m_Size.y - m_VScrollBarRect->m_Size.y) * 0.5;
    }

    if (m_HScrollBarRect != nullptr)
    {
        m_ScrollBarMaxRange.x = (m_HScrollRect->m_Size.x - m_HScrollBarRect->m_Size.x) * 0.5;
        m_ScrollBarMinRange.x = -(m_HScrollRect->m_Size.x - m_HScrollBarRect->m_Size.x) * 0.5;
    }
}

//�������ڽ��� ���� ������ ����
void ViewBox::CalcContentMovableRange()
{
    //��ڽ��� �������ڽ��� ����, ���� ���
    //���̿� ���̸� ��� �������� ������ �� ���̸� ���ϰ�
    //��ڽ��� ��ġ ���� +- ���� ���̰��� ���� ����
    if (m_ContentRect != nullptr && m_Rect != nullptr)
    {
        m_ContentMaxRange.x = (m_ContentRect->m_Size.x - m_Rect->m_Size.x) * 0.5;
        m_ContentMaxRange.y = (m_ContentRect->m_Size.y - m_Rect->m_Size.y) * 0.5;
        m_ContentMinRange.x = -(m_ContentRect->m_Size.x - m_Rect->m_Size.x) * 0.5;
        m_ContentMinRange.y = -(m_ContentRect->m_Size.y - m_Rect->m_Size.y) * 0.5;
    }
}

//���� ���� �� ���� ��ġ�� 0~1������ ������ ��ȯ��()
Vector2 ViewBox::NormalizePosition(Vector2 p_CurrentPos, Vector2 p_MinPos, Vector2 p_MaxPos)
{
    Vector2 normal;

    normal.x = p_CurrentPos.x / (p_MaxPos.x - p_MinPos.x) + 0.5;
    normal.y = p_CurrentPos.y / (p_MaxPos.y - p_MinPos.y) + 0.5;

    return normal;
}

Vector2 ViewBox::DisNormalizePosition(Vector2 p_Normal, Vector2 p_MinPos, Vector2 p_MaxPos)
{
    Vector2 pos;

    pos.x = (p_Normal.x - 0.5) * (p_MaxPos.x - p_MinPos.x);
    pos.y = (p_Normal.y - 0.5) * (p_MaxPos.y - p_MinPos.y);

    return pos;
}

Vector2 ViewBox::GetScrollBarMinRange()
{
    return m_ScrollBarMinRange;
}

Vector2 ViewBox::GetScrollBarMaxRange()
{
    return m_ScrollBarMaxRange;
}

void ViewBox::AdjustScrollBarSize()
{
    if (m_Rect == nullptr) return;
    Vector2 viewrect = m_Rect->m_Size;

    if (m_ContentRect == nullptr) return;
    Vector2 contrect = m_ContentRect->m_Size;

    //��ڽ��� ������ �ڽ��� ��%�� �����ְ� �ִ��� ����
    Vector2 percent;
    percent.x = viewrect.x / contrect.x;
    percent.y = viewrect.y / contrect.y;

    //�ʹ� �۾����� �ȵǹǷ� ũ�� ���Ѽ� ����
    if (percent.x < 0.1) percent.x = 0.1;
    if (percent.y < 0.1) percent.y = 0.1;

    //���� ��ũ�ѹٰ� �����Ҷ�
    if (m_HScrollBarRect != nullptr)
    {
        //��ũ�ѹٰ� ��Ȱ��ȭ �����϶� �������ڽ��� ũ�Ⱑ ��ڽ��� �Ѿ�� Ȱ��ȭ
        if (m_HScrollBarRect->gameObject->isActive() == false && percent.x < 1)
        {
            m_HScrollBarRect->gameObject->SetActive(true);
            m_HScrollRect->gameObject->SetActive(true);
        }

        //100% �� �����ְ� ������ ��ũ�ѹٰ� �ʿ� �����Ƿ� ��ũ�Ѱ� ��ũ�ѹ� ��Ȱ��ȭ
        if (percent.x >= 1)
        {
            m_HScrollBarRect->gameObject->SetActive(false);
            m_HScrollRect->gameObject->SetActive(false);
        }

        m_HScrollBarRect->m_Size.x = m_HScrollRect->m_Size.x * percent.x;
        m_HScrollBarRect->m_Size.y = m_HScrollRect->m_Size.y;
    }

    //���� ��ũ�ѹٰ� �����Ҷ�
    if (m_VScrollBarRect != nullptr)
    {
        //��ũ�ѹٰ� ��Ȱ��ȭ �����϶� �������ڽ��� ũ�Ⱑ ��ڽ��� �Ѿ�� Ȱ��ȭ
        if (m_VScrollBarRect->gameObject->isActive() == false && percent.y < 1)
        {
            m_VScrollBarRect->gameObject->SetActive(true);
            m_VScrollBarRect->gameObject->SetActive(true);
        }

        //100% �� �����ְ� ������ ��ũ�ѹٰ� �ʿ� �����Ƿ� ��ũ�Ѱ� ��ũ�ѹ� ��Ȱ��ȭ
        if (percent.y >= 1)
        {
            m_VScrollBarRect->gameObject->SetActive(false);
            m_VScrollRect->gameObject->SetActive(false);
        }

        m_VScrollBarRect->m_Size.x = m_VScrollRect->m_Size.x;
        m_VScrollBarRect->m_Size.y = m_VScrollRect->m_Size.y * percent.y;
    }

    //����� �������Ƿ� ���� ���� �ٽ� ���
    CalcScrollMovableRange();
    //���� ������ �������Ƿ� ���� ��ġ �ٽ� ���
    UpdateScrollBar();
}

//�������ڽ� ������ �ø��� �ø� ������ ���ݸ�ŭ ����
void ViewBox::ExtendContentBoxSizeX()
{
    if (m_ContentRect == nullptr) return;
    Vector2 temppos = m_ContentRect->GetPosition();
    Vector2 tempChildpos;

    int test = 50;

    //������ �̾� ���̴� ������ �ø��� ���̱� ������ ������ �ڽ��� ��ġ ����
    m_ContentRect->m_Size.x += test;
    temppos.x += test * 0.5;
    m_ContentRect->SetPosition(temppos);

    //������ �ڽ��� ���Ե� ������Ʈ���� ��ġ�� ���� ����
    for (int i = 0; i < m_ContentRect->GetChildCount(); i++)
    {
        tempChildpos = m_ContentRect->GetChild(i)->GetPosition();
        tempChildpos.x -= test * 0.5;
        m_ContentRect->GetChild(i)->SetPosition(tempChildpos);
    }

    //�������ڽ� ũ�Ⱑ �������Ƿ� �������ڽ� �������� �ٽ� ���ϰ�
    CalcContentMovableRange();
    //��ũ�ѹٵ� ���� ������
    AdjustScrollBarSize();
}

//�������ڽ� ������ �ø��� �ø� ������ ���ݸ�ŭ ����
void ViewBox::ExtendContentBoxSizeY()
{
    if (m_ContentRect == nullptr) return;
    Vector2 temppos = m_ContentRect->GetPosition();
    Vector2 tempChildpos;

    int test = 50;

    //������ �̾� ���̴� ������ �ø��� ���̱� ������ ������ �ڽ��� ��ġ ����
    m_ContentRect->m_Size.y += test;
    temppos.y += test * 0.5;
    m_ContentRect->SetPosition(temppos);

    //������ �ڽ��� ���Ե� ������Ʈ���� ��ġ�� ���� ����
    for (int i = 0; i < m_ContentRect->GetChildCount(); i++)
    {
        tempChildpos = m_ContentRect->GetChild(i)->GetPosition();
        tempChildpos.y -= test * 0.5;
        m_ContentRect->GetChild(i)->SetPosition(tempChildpos);
    }

    //�������ڽ� ũ�Ⱑ �������Ƿ� �������ڽ� �������� �ٽ� ���ϰ�
    CalcContentMovableRange();
    //��ũ�ѹٵ� ���� ������
    AdjustScrollBarSize();
}

Vector2 ViewBox::GetContentBoxSize()
{
    return m_ContentRect->m_Size;
}

void ViewBox::OnMouseDown()
{
    m_isDown = true;
    m_MousePrePos = Input::MousePosition;
}

void ViewBox::OnWheelUp()
{
    if (m_ContentRect == nullptr) return;

    Vector2 contPos = m_ContentRect->GetPosition();

    Vector2 normal = NormalizePosition(contPos, m_ContentMinRange, m_ContentMaxRange);

    //����ƮŰ�� ���� ���¶�� �������� ��ũ��, �ƴ϶�� ���� ��ũ��
    if (GetInputBuffer(KeyHold, VK_SHIFT))
    {
        if (normal.x <= 1)
        {
            contPos.x += 5;
            m_ContentRect->SetPosition(contPos);
        }

        normal = NormalizePosition(contPos, m_ContentMinRange, m_ContentMaxRange);

        if (normal.x > 1)
        {
            normal.x = 1;
            Vector2 temp = DisNormalizePosition(normal, m_ContentMinRange, m_ContentMaxRange);
            m_ContentRect->SetPosition(temp);
        }
    }
    else
    {
        if (normal.y <= 1)
        {
            contPos.y += 5;
            m_ContentRect->SetPosition(contPos);
        }

        normal = NormalizePosition(contPos, m_ContentMinRange, m_ContentMaxRange);

        if (normal.y > 1)
        {
            normal.y = 1;
            Vector2 temp = DisNormalizePosition(normal, m_ContentMinRange, m_ContentMaxRange);
            m_ContentRect->SetPosition(temp);
        }
    }

    //�������ڽ��� ��ġ ���濡 ���� ��ũ�ѹ� ��ġ ����
    UpdateScrollBar();
}

void ViewBox::OnWheelDown()
{
    if (m_ContentRect == nullptr) return;
    
    Vector2 contPos = m_ContentRect->GetPosition();

    Vector2 normal = NormalizePosition(contPos, m_ContentMinRange, m_ContentMaxRange);

    //����ƮŰ�� ���� ���¶�� ���������� ��ũ��, �ƴ϶�� �Ʒ��� ��ũ��
    if (GetInputBuffer(KeyHold, VK_SHIFT))
    {
        if (normal.x >= 0)
        {
            contPos.x -= 5;
            m_ContentRect->SetPosition(contPos);
        }

        normal = NormalizePosition(contPos, m_ContentMinRange, m_ContentMaxRange);

        if (normal.x < 0)
        {
            //�������ڽ� ���̰� 700 �̸��̸� ���������� �����̵��� ����
            if (m_ContentRect->m_Size.x < 700)
            {
                ExtendContentBoxSizeX();

                //�������ڽ� ũ�� ���� �������� �������ڽ��� ũ��� ��ġ�� �ٲ�Ƿ� ������ ��ġ�� ������������ �ٽ� �ѹ� ����ȭ
                contPos = m_ContentRect->GetPosition();
                contPos.x -= 5;

                normal = NormalizePosition(contPos, m_ContentMinRange, m_ContentMaxRange);
            }
            else
            {
                normal.x = 0;
            }

            Vector2 temp = DisNormalizePosition(normal, m_ContentMinRange, m_ContentMaxRange);
            m_ContentRect->SetPosition(temp);
        }
    }
    else
    {
        if (normal.y >= 0)
        {
            contPos.y -= 5;
            m_ContentRect->SetPosition(contPos);
        }

        normal = NormalizePosition(contPos, m_ContentMinRange, m_ContentMaxRange);

        if (normal.y < 0)
        {
            //�������ڽ� ���̰� 700 �̸��̸� �Ʒ��� �����̵��� ����
            if (m_ContentRect->m_Size.y < 700)
            {
                ExtendContentBoxSizeY();

                //�������ڽ� ũ�� ���� �������� �������ڽ��� ũ��� ��ġ�� �ٲ�Ƿ� ������ ��ġ�� ������������ �ٽ� �ѹ� ����ȭ
                contPos = m_ContentRect->GetPosition();
                contPos.y -= 5;

                normal = NormalizePosition(contPos, m_ContentMinRange, m_ContentMaxRange);
            }
            else
            {
                normal.y = 0;
            }

            Vector2 temp = DisNormalizePosition(normal, m_ContentMinRange, m_ContentMaxRange);
            m_ContentRect->SetPosition(temp);
        }
    }

    //�������ڽ��� ��ġ ���濡 ���� ��ũ�ѹ� ��ġ ����
    UpdateScrollBar();
}