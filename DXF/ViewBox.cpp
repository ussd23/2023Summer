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

        CalcScrollMovableRange();
        CalcContentMovableRange();
    }
}

void ViewBox::Update()
{
    if (m_ContentRect == nullptr) return;

    if (m_isDown)
    {
        Vector2 testnormal;

        Vector2 gap;
        Vector2 childLT, childRB, rectLT, rectRB;

        Vector2 pos = m_Rect->GetScreenPosition();
        Vector2 childPos = m_ContentRect->GetScreenPosition();

        test = NormalizePosition(m_ContentRect->GetPosition(), m_ContentMinRange, m_ContentMaxRange);

        childLT.x = childPos.x - (m_ContentRect->m_Size.x * 0.5);   //contentbox������ ��ǥ
        childLT.y = childPos.y - (m_ContentRect->m_Size.y * 0.5);   //contentbox������ ��ǥ

        childRB.x = childPos.x + (m_ContentRect->m_Size.x * 0.5);   //contentbox������ ��ǥ
        childRB.y = childPos.y + (m_ContentRect->m_Size.y * 0.5);   //contentbox������ ��ǥ

        rectLT.x = pos.x - (m_Rect->m_Size.x * 0.5);      //viewbox������ ��ǥ
        rectLT.y = pos.y - (m_Rect->m_Size.y * 0.5);      //viewbox������ ��ǥ

        rectRB.x = pos.x + (m_Rect->m_Size.x * 0.5);      //viewbox������ ��ǥ
        rectRB.y = pos.y + (m_Rect->m_Size.y * 0.5);      //viewbox������ ��ǥ

        //�������ڽ��� ��/�������� ��ڽ��� ��/�������� �ۿ� ������ x���̵� ����
        if (childLT.x < rectLT.x && childRB.x > rectRB.x)
        {
            Vector2 temppos = m_ContentRect->GetPosition();
            temppos.x = temppos.x + (Input::MousePosition.x - m_MousePrePos.x);
            m_ContentRect->SetPosition(temppos);
        }
        //�������ڽ��� ��/�������� ��ڽ��� ��/�������� ������ �ش� ���������� �̵��� ����
        else if (childLT.x == rectLT.x)
        {
            if (Input::MousePosition.x < m_MousePrePos.x)
            {
                Vector2 temppos = m_ContentRect->GetPosition();
                temppos.x = temppos.x + (Input::MousePosition.x - m_MousePrePos.x);
                m_ContentRect->SetPosition(temppos);
            }
        }
        else if (childRB.x == rectRB.x)
        {
            if (Input::MousePosition.x > m_MousePrePos.x)
            {
                Vector2 temppos = m_ContentRect->GetPosition();
                temppos.x = temppos.x + (Input::MousePosition.x - m_MousePrePos.x);
                m_ContentRect->SetPosition(temppos);
            }
        }

        //�������ڽ��� �������� ��ڽ��� �������� �ȿ� ������ �� ��ġ ����
        if (childLT.x > rectLT.x)
        {
            gap.x = childLT.x - rectLT.x;

            Vector2 temppos = m_ContentRect->GetPosition();
            temppos.x -= gap.x;
            m_ContentRect->SetPosition(temppos);
        }
        //�������ڽ��� �������� ��ڽ��� �������� �ȿ� ������ �� ��ġ ����
        if (childRB.x < rectRB.x)
        {
            gap.x = childRB.x - rectRB.x;

            Vector2 temppos = m_ContentRect->GetPosition();
            temppos.x -= gap.x;
            m_ContentRect->SetPosition(temppos);
        }

        //y�൵ �Ȱ��� ����
        if (childLT.y < rectLT.y && childRB.y > rectRB.y)
        {
            Vector2 temppos = m_ContentRect->GetPosition();
            temppos.y = temppos.y + (Input::MousePosition.y - m_MousePrePos.y);
            m_ContentRect->SetPosition(temppos);
        }
        else if (childLT.y == rectLT.y)
        {
            if (Input::MousePosition.y < m_MousePrePos.y)
            {
                Vector2 temppos = m_ContentRect->GetPosition();
                temppos.y = temppos.y + (Input::MousePosition.y - m_MousePrePos.y);
                m_ContentRect->SetPosition(temppos);
            }
        }
        else if (childRB.y == rectRB.y)
        {
            if (Input::MousePosition.y > m_MousePrePos.y)
            {
                Vector2 temppos = m_ContentRect->GetPosition();
                temppos.y = temppos.y + (Input::MousePosition.y - m_MousePrePos.y);
                m_ContentRect->SetPosition(temppos);
            }
        }

        if (childLT.y > rectLT.y)
        {
            gap.y = childLT.y - rectLT.y;

            Vector2 temppos = m_ContentRect->GetPosition();
            temppos.y -= gap.y;
            m_ContentRect->SetPosition(temppos);
        }
        if (childRB.y < rectRB.y)
        {
            gap.y = childRB.y - rectRB.y;

            Vector2 temppos = m_ContentRect->GetPosition();
            temppos.y -= gap.y;
            m_ContentRect->SetPosition(temppos);
        }

        m_MousePrePos = Input::MousePosition;
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
    //���� �������� �������ڽ� �̵� ���°͵� �̰� ����ϵ��� ����
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

//�������ڽ����� ���� ������ ���ϰ� �ش� ���� �������� ��ġ���� 0~1 ������ ������ ��ȯ
//�ش� ���� ��ũ�ٰ� �޾Ƽ� ������ ���� ������ ����
//�ݴ뵵 ��������
//���� ���� ��ڽ��� �� �����ϰ� ����� �ɵ�
//�ʿ��Ѱ�> �������� ���ϴ� �Լ�, ���� ������ ���� ���� ���ϴ� �Լ�

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
    Vector2 gap;
    Vector2 childLT, childRB, rectLT, rectRB;

    Vector2 pos = m_Rect->GetScreenPosition();
    Vector2 childPos = m_ContentRect->GetScreenPosition();

    childLT.x = childPos.x - (m_ContentRect->m_Size.x * 0.5);   //contentbox������ ��ǥ
    childLT.y = childPos.y - (m_ContentRect->m_Size.y * 0.5);   //contentbox������ ��ǥ

    childRB.x = childPos.x + (m_ContentRect->m_Size.x * 0.5);   //contentbox������ ��ǥ
    childRB.y = childPos.y + (m_ContentRect->m_Size.y * 0.5);   //contentbox������ ��ǥ

    rectLT.x = pos.x - (m_Rect->m_Size.x * 0.5);      //viewbox������ ��ǥ
    rectLT.y = pos.y - (m_Rect->m_Size.y * 0.5);      //viewbox������ ��ǥ

    rectRB.x = pos.x + (m_Rect->m_Size.x * 0.5);      //viewbox������ ��ǥ
    rectRB.y = pos.y + (m_Rect->m_Size.y * 0.5);      //viewbox������ ��ǥ


    if (childLT.y < rectLT.y)
    {
        Vector2 temppos = m_ContentRect->GetPosition();
        temppos.y += 5;
        m_ContentRect->SetPosition(temppos);
    }

    if (childLT.y > rectLT.y)
    {
        gap.y = childLT.y - rectLT.y;

        Vector2 temppos = m_ContentRect->GetPosition();
        temppos.y -= gap.y;
        m_ContentRect->SetPosition(temppos);
    }
}

void ViewBox::OnWheelDown()
{
    Vector2 gap;
    Vector2 childLT, childRB, rectLT, rectRB;

    Vector2 pos = m_Rect->GetScreenPosition();
    Vector2 childPos = m_ContentRect->GetScreenPosition();

    childLT.x = childPos.x - (m_ContentRect->m_Size.x * 0.5);   //contentbox������ ��ǥ
    childLT.y = childPos.y - (m_ContentRect->m_Size.y * 0.5);   //contentbox������ ��ǥ

    childRB.x = childPos.x + (m_ContentRect->m_Size.x * 0.5);   //contentbox������ ��ǥ
    childRB.y = childPos.y + (m_ContentRect->m_Size.y * 0.5);   //contentbox������ ��ǥ

    rectLT.x = pos.x - (m_Rect->m_Size.x * 0.5);      //viewbox������ ��ǥ
    rectLT.y = pos.y - (m_Rect->m_Size.y * 0.5);      //viewbox������ ��ǥ

    rectRB.x = pos.x + (m_Rect->m_Size.x * 0.5);      //viewbox������ ��ǥ
    rectRB.y = pos.y + (m_Rect->m_Size.y * 0.5);      //viewbox������ ��ǥ

    if (childRB.y > rectRB.y)
    {
        Vector2 temppos = m_ContentRect->GetPosition();
        temppos.y -= 5;
        m_ContentRect->SetPosition(temppos);
    }

    if (childRB.y < rectRB.y)
    {
        gap.y = childRB.y - rectRB.y;

        Vector2 temppos = m_ContentRect->GetPosition();
        temppos.y -= gap.y;
        m_ContentRect->SetPosition(temppos);
    }
}

//�巡�׷� �̵�, ���콺 �ٷ� �̵� �Ϸ�
//��ũ�ѹ� �߰��ϱ�, ��ڽ� ���� �Ѿ �̹��� �ڸ��� �ؾ���5