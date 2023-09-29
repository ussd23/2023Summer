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
                m_PreContentPos = m_ContentRect->GetPosition();
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
                    m_PreScrollBarPos.y = m_VScrollBarRect->GetPosition().y;
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
                    m_PreScrollBarPos.x = m_HScrollBarRect->GetPosition().x;
                }
            }
        }

        CalcContentMovableRange();
        AdjustScrollBarSize();
    }
}

void ViewBox::Update()
{
    if (m_ContentRect == nullptr) return;

    if (m_isDown)
    {
        MoveContentBox();

        //���콺 ��ġ ����
        m_MousePrePos = Input::MousePosition;
    }
}

void ViewBox::MoveContentBox()
{
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
        normal.x = 0;
    }

    //������ ��ġ�� ���� ���� �Ѱ踦 ������ ��ġ�� �Ѱ�ġ�� ����
    if (normal.y > 1)
    {
        normal.y = 1;
    }
    //������ ��ġ�� ���� ���� �Ѱ踦 ������ ��ġ�� �Ѱ�ġ�� ����
    else if (normal.y < 0)
    {
        normal.y = 0;
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
    Vector2 contPos = m_ContentRect->GetPosition();
    Vector2 vscbPos = m_VScrollBarRect->GetPosition();
    Vector2 hscbPos = m_HScrollBarRect->GetPosition();

    Vector2 tempPos;
    tempPos.x = hscbPos.x;
    tempPos.y = vscbPos.y;

    Vector2 normal = NormalizePosition(tempPos, m_ScrollBarMinRange, m_ScrollBarMaxRange);
    normal.x = 1 - normal.x;
    normal.y = 1 - normal.y;

    tempPos = DisNormalizePosition(normal, m_ContentMinRange, m_ContentMaxRange);

    m_ContentRect->SetPosition(tempPos);
}

//�������ڽ��� ��ġ ���濡 ���� ��ũ�ѹ� ��ġ ����
void ViewBox::UpdateScrollBar()
{
    Vector2 contPos = m_ContentRect->GetPosition();
    Vector2 vscbPos = m_VScrollBarRect->GetPosition();
    Vector2 hscbPos = m_HScrollBarRect->GetPosition();

    Vector2 normal = NormalizePosition(contPos, m_ContentMinRange, m_ContentMaxRange);
    normal.x = 1 - normal.x;
    normal.y = 1 - normal.y;

    Vector2 tempPos = DisNormalizePosition(normal, m_ScrollBarMinRange, m_ScrollBarMaxRange);
    vscbPos.y = tempPos.y;
    hscbPos.x = tempPos.x;

    m_VScrollBarRect->SetPosition(vscbPos);
    m_HScrollBarRect->SetPosition(hscbPos);
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
    if (m_ContentRect != nullptr)
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
    Vector2 contrect = m_ContentRect->m_Size;
    Vector2 viewrect = m_Rect->m_Size;

    Vector2 temp;
    temp.x = viewrect.x / contrect.x;
    temp.y = viewrect.y / contrect.y;

    m_HScrollBarRect->m_Size.x = m_HScrollRect->m_Size.x * temp.x;
    m_HScrollBarRect->m_Size.y = m_HScrollRect->m_Size.y;
    
    m_VScrollBarRect->m_Size.x = m_VScrollRect->m_Size.x;
    m_VScrollBarRect->m_Size.y = m_VScrollRect->m_Size.y * temp.y;

    //����� �������Ƿ� ���� ���� �ٽ� ���
    CalcScrollMovableRange();
    //���� ������ �������Ƿ� ���� ��ġ �ٽ� ���
    UpdateScrollBar();
}

//��ڽ��� ũ��� �������ڽ��� ũ���� ���̿� ���� ��ũ�ѹ� ũ�� ����(0.1~1)
//��ũ�ѹ� ũ�Ⱑ 1�̵Ǹ� ��ũ�� ��Ȱ��ȭ

//�������ڽ��� ���� �ְ����� �����ϸ� ������ �ø��� �ø� ������ ���ݸ�ŭ ������ ��� �߰�

void ViewBox::OnMouseDown()
{
    m_isDown = true;
    m_MousePrePos = Input::MousePosition;
}

void ViewBox::OnMouseUp()
{
    m_isDown = false;
}

void ViewBox::OnMouseExit()
{
    m_isDown = false;
}

void ViewBox::OnWheelUp()
{
    Vector2 contPos = m_ContentRect->GetPosition();

    Vector2 normal = NormalizePosition(contPos, m_ContentMinRange, m_ContentMaxRange);

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

    //�������ڽ��� ��ġ ���濡 ���� ��ũ�ѹ� ��ġ ����
    UpdateScrollBar();
}

void ViewBox::OnWheelDown()
{
    Vector2 contPos = m_ContentRect->GetPosition();

    Vector2 normal = NormalizePosition(contPos, m_ContentMinRange, m_ContentMaxRange);

    if (normal.y >= 0)
    {
        contPos.y -= 5;
        m_ContentRect->SetPosition(contPos);
    }

    normal = NormalizePosition(contPos, m_ContentMinRange, m_ContentMaxRange);

    if (normal.y < 0)
    {
        normal.y = 0;
        Vector2 temp = DisNormalizePosition(normal, m_ContentMinRange, m_ContentMaxRange);
        m_ContentRect->SetPosition(temp);
    }

    //�������ڽ��� ��ġ ���濡 ���� ��ũ�ѹ� ��ġ ����
    UpdateScrollBar();
}