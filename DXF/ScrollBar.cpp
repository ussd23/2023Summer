#include "ComponentHeader.h"

void ScrollBar::Awake()
{
    m_Rect = GetComponentFromObject(gameObject, RectTransform);
    if (m_Rect == nullptr) return;

    RectTransform* parentrect = m_Rect->GetParent();
    if (parentrect == nullptr) return;

    m_ParentScroll = GetComponentFromObject(parentrect->gameObject, Scroll);
    if (m_ParentScroll == nullptr) return;

    RectTransform* parentparentrect = parentrect->GetParent();
    if (parentparentrect == nullptr) return;

    m_ParentView = GetComponentFromObject(parentparentrect->gameObject, ViewBox);
    if (m_ParentView == nullptr) return;


    if (m_ParentScroll->GetIsVertical())
    {
        //scroll�� ScrollBar�� ���� ����
        m_Rect->m_Size.y = parentrect->m_Size.y * 0.3;
    }
    else
    {
        //scroll�� ScrollBar�� ���� ����
        m_Rect->m_Size.x = parentrect->m_Size.x * 0.3;
    }

}

void ScrollBar::Start()
{
    m_ParentView->UpdateScrollBar();
}

void ScrollBar::Update()
{
    if (m_isDown)
    {
        MoveScrollBar();

        //���콺 ��ġ ����
        m_MousePrePos = Input::MousePosition;
    }
}

void ScrollBar::MoveScrollBar()
{
    if (m_Rect == nullptr) return;

    Vector2 Pos;

    if (m_ParentScroll->GetIsVertical())
    {
        Pos.x = 0;
        Pos.y = m_Rect->GetPosition().y;
    }
    else
    {
        Pos.x = m_Rect->GetPosition().x;
        Pos.y = 0;
    }

    Vector2 normal = m_ParentView->NormalizePosition(Pos, m_ParentView->GetScrollBarMinRange(), m_ParentView->GetScrollBarMaxRange());

    if (!m_ParentScroll->GetIsVertical())
    {
        //���� ���� �Ѱ迡 �����Ѱ�� �������θ� ������ �� �ְ� ��
        if (normal.x == 1)
        {
            if (Input::MousePosition.x < m_MousePrePos.x)
            {
                Pos.x = Pos.x + (Input::MousePosition.x - m_MousePrePos.x);
            }
        }
        //���� ���� �Ѱ迡 �����Ѱ�� ���������θ� ������ �� �ְ� ��
        else if (normal.x == 0)
        {
            if (Input::MousePosition.x > m_MousePrePos.x)
            {
                Pos.x = Pos.x + (Input::MousePosition.x - m_MousePrePos.x);
            }
        }
        //����ʵ� �ƴ϶�� �����Ӱ� ������ �� �ְ� ��
        else
        {
            Pos.x = Pos.x + (Input::MousePosition.x - m_MousePrePos.x);
        }

        //������ ��ġ�� �ٽ� �ѹ� ����ȭ
        normal = m_ParentView->NormalizePosition(Pos, m_ParentView->GetScrollBarMinRange(), m_ParentView->GetScrollBarMaxRange());

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
    }
    else
    {
        //���� ���� �Ѱ迡 �����Ѱ�� �������θ� ������ �� �ְ� ��
        if (normal.y == 1)
        {
            if (Input::MousePosition.y < m_MousePrePos.y)
            {
                Pos.y = Pos.y + (Input::MousePosition.y - m_MousePrePos.y);
            }
        }
        //���� ���� �Ѱ迡 �����Ѱ�� �Ʒ������θ� ������ �� �ְ� ��
        else if (normal.y == 0)
        {
            if (Input::MousePosition.y > m_MousePrePos.y)
            {
                Pos.y = Pos.y + (Input::MousePosition.y - m_MousePrePos.y);
            }
        }
        //����ʵ� �ƴ϶�� �����Ӱ� ������ �� �ְ� ��
        else
        {
            Pos.y = Pos.y + (Input::MousePosition.y - m_MousePrePos.y);
        }

        //������ ��ġ�� �ٽ� �ѹ� ����ȭ
        normal = m_ParentView->NormalizePosition(Pos, m_ParentView->GetScrollBarMinRange(), m_ParentView->GetScrollBarMaxRange());

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
    }

    //���� ������ ��ġ�� ��ũ�ѹٿ� ����
    Vector2 tempPos = m_ParentView->DisNormalizePosition(normal, m_ParentView->GetScrollBarMinRange(), m_ParentView->GetScrollBarMaxRange());
    m_Rect->SetPosition(tempPos);

    //��ũ�ѹ��� ��ġ ���濡 ���� �������ڽ� ��ġ ����
    m_ParentView->UpdateContentBox();
}

void ScrollBar::OnMouseDown()
{
    m_isDown = true;
    m_MousePrePos = Input::MousePosition;
}

void ScrollBar::OnMouseUp()
{
    m_isDown = false;
}

void ScrollBar::OnMouseExit()
{
    m_isDown = false;
}