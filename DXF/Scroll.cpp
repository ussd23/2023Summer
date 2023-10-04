#include "ComponentHeader.h"

Scroll::Scroll(bool p_IsVertical)
{
    m_IsVertical = p_IsVertical;
}

void Scroll::Awake()
{
    RectTransform* rect = GetComponentFromObject(gameObject, RectTransform);
    if (rect == nullptr) return;

    RectTransform* parentrect = rect->GetParent();
    if (parentrect == nullptr) return;

    m_ScrollBarRect = rect->GetChild(0);
    if (m_ScrollBarRect == nullptr) return;

    m_ParentView = GetComponentFromObject(rect->GetParent()->gameObject, ViewBox);
    if (m_ParentView == nullptr) return;

    if (m_IsVertical)
    {
        rect->m_Size.y = parentrect->m_Size.y;
    }
    else
    {
        rect->m_Size.x = parentrect->m_Size.x - 15;
    }
}

void Scroll::Start()
{
    AdjustPosition();
}

void Scroll::OnMouseDown()
{
    //��ũ�ѹ� ��ġ�� Ŭ�� ��ġ�� ���� ���� �����ϰ� ��ũ�ѹ� �̵�
    //�� ��ũ�ѹ� �̵��� ����ġ * ��ũ�ѹ� ũ�⸸ŭ �̵�
    RectTransform* rect = GetComponentFromObject(gameObject, RectTransform);
    if (rect == nullptr) return;

    m_isDown = true;
    m_ClickTime = GetTickCount64();

    Vector2 barPos = m_ScrollBarRect->GetPosition();
    Vector2 barScreenPos = m_ScrollBarRect->GetScreenPosition();

    Vector2 percent;
    percent.x = m_ScrollBarRect->m_Size.x / rect->m_Size.x;
    percent.y = m_ScrollBarRect->m_Size.y / rect->m_Size.y;


    if (m_IsVertical)
    {
        if (barScreenPos.y > Input::MousePosition.y)
        {
            barPos.y -= 15 * percent.y;
        }
        else
        {
            barPos.y += 15 * percent.y;
        }
    }
    else
    {
        if (barScreenPos.x > Input::MousePosition.x)
        {
            barPos.x -= 15 * percent.x;
        }
        else
        {
            barPos.x += 15 * percent.x;
        }
    }
    m_ScrollBarRect->SetPosition(barPos);
    m_ParentView->UpdateContentBox();
}

void Scroll::OnMouseHold()
{
    //��ũ�ѹ� ��ġ�� ���콺 ��ġ�� ���� ���� �����ϰ� ��ũ�ѹ� �̵�
    //�� ��ũ�ѹ� �̵��� ����ġ * ��ũ�ѹ� ũ�⸸ŭ�� �ӵ��� �̵�
    RectTransform* rect = GetComponentFromObject(gameObject, RectTransform);
    if (rect == nullptr) return;

    Vector2 barPos = m_ScrollBarRect->GetPosition();
    Vector2 barScreenPos = m_ScrollBarRect->GetScreenPosition();

    Vector2 percent;
    percent.x = m_ScrollBarRect->m_Size.x / rect->m_Size.x;
    percent.y = m_ScrollBarRect->m_Size.y / rect->m_Size.y;

    if (m_isDown)
    {
        if (GetTickCount64() > m_ClickTime + 200)
        {
            if (m_IsVertical)
            {
                if (barScreenPos.y > Input::MousePosition.y)
                {
                    barPos.y -= 10 * percent.y;
                }
                else
                {
                    barPos.y += 10 * percent.y;
                }
            }
            else
            {
                if (barScreenPos.x > Input::MousePosition.x)
                {
                    barPos.x -= 10 * percent.x;
                }
                else
                {
                    barPos.x += 10 * percent.x;
                }
            }
            m_ScrollBarRect->SetPosition(barPos);
            m_ParentView->UpdateContentBox();
        }
    }
}

void Scroll::OnMouseUp()
{
    m_isDown = false;
}

void Scroll::OnMouseExit()
{
    m_isDown = false;
}

bool Scroll::GetIsVertical()
{
    return m_IsVertical;
}

void Scroll::AdjustPosition()
{
    RectTransform* rect = GetComponentFromObject(gameObject, RectTransform);
    if (rect == nullptr) return;

    RectTransform* parentrect = rect->GetParent();
    if (parentrect == nullptr) return;

    Vector2 gap, point1, point2, pos;

    if (m_IsVertical)
    {
        //viewbox�� ������ ��ǥ ������
        point1.x = parentrect->GetPosition().x + (parentrect->m_Size.x * 0.5);

        pos = rect->GetScreenPosition();
        //Scroll�� ������ ��ǥ ������
        point2.x = pos.x + (rect->m_Size.x * 0.5);

        //viewbox�� Scroll�� ���� �� ������ �Ÿ� ���
        gap.x = point2.x - point1.x;

        //��ڽ��� ���� ���� ��ũ���� ��ġ�ϵ��� ����
        rect->SetPosition(Vector2(rect->GetPosition().x - gap.x, 0));

        //��ڽ��� ��ũ���� ���� �����ϰ� ����
        rect->m_Size.y = parentrect->m_Size.y;
    }
    else
    {
        //viewbox�� ������ ��ǥ ������
        point1.y = parentrect->GetPosition().y + (parentrect->m_Size.y * 0.5);

        pos = rect->GetScreenPosition();
        //Scroll�� ������ ��ǥ ������
        point2.y = pos.y + (rect->m_Size.y * 0.5);

        //viewbox�� Scroll�� ������ ������ �Ÿ� ���
        gap.y = point2.y - point1.y;

        //��ڽ��� �������� ��ũ���� ��ġ�ϵ��� ����
        rect->SetPosition(Vector2(-7.5f, rect->GetPosition().y - gap.y));

        //��ũ���� ���� ����
        rect->m_Size.x = parentrect->m_Size.x - 15;
    }
}