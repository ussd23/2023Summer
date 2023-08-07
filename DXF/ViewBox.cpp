#include "ComponentHeader.h"

ViewBox::ViewBox()
{
    m_Spr = new SpriteRenderer("default.png", 0xff606060, Vector2(1, 1), Vector2(0, 0));
    m_Mouse = new MouseFunction();
}

ViewBox::ViewBox(Vector2 _rectsize, Vector2 _rectindex)
{
    m_Spr = new SpriteRenderer("default.png", 0xff606060, _rectsize, _rectindex);
    m_Mouse = new MouseFunction();
}

ViewBox::ViewBox(DWORD _color, Vector2 _rectsize, Vector2 _rectindex)
{
    m_Spr = new SpriteRenderer("default.png", _color, _rectsize, _rectindex);
    m_Mouse = new MouseFunction();
}

void ViewBox::Start()
{
    AddComponentToObject(gameObject, m_Spr);
    AddComponentToObject(gameObject, m_Mouse);

    rect = GetComponentFromObject(gameObject, RectTransform);
    child = rect->GetChild(0);
}

void ViewBox::Update()
{
    if (m_Isdown)
    {
        Vector2 gap;
        Vector2 childLT, childRB, rectLT, rectRB;

        childLT.x = child->GetScreenPosition().x - (child->size.x * 0.5);   //contentbox������ ��ǥ
        childLT.y = child->GetScreenPosition().y - (child->size.y * 0.5);   //contentbox������ ��ǥ

        childRB.x = child->GetScreenPosition().x + (child->size.x * 0.5);   //contentbox������ ��ǥ
        childRB.y = child->GetScreenPosition().y + (child->size.y * 0.5);   //contentbox������ ��ǥ

        rectLT.x = rect->GetScreenPosition().x - (rect->size.x * 0.5);      //viewbox������ ��ǥ
        rectLT.y = rect->GetScreenPosition().y - (rect->size.y * 0.5);      //viewbox������ ��ǥ

        rectRB.x = rect->GetScreenPosition().x + (rect->size.x * 0.5);      //viewbox������ ��ǥ
        rectRB.y = rect->GetScreenPosition().y + (rect->size.y * 0.5);      //viewbox������ ��ǥ

        //�������ڽ��� ��/�������� ��ڽ��� ��/�������� �ۿ� ������ x���̵� ����
        if (childLT.x < rectLT.x && childRB.x > rectRB.x)
        {
            child->position.x = child->position.x + (g_mousepos.x - m_MousePrePos.x);
        }
        //�������ڽ��� ��/�������� ��ڽ��� ��/�������� ������ �ش� ���������� �̵��� ����
        else if (childLT.x == rectLT.x)
        {
            if (g_mousepos.x < m_MousePrePos.x)
            {
                child->position.x = child->position.x + (g_mousepos.x - m_MousePrePos.x);
            }
        }
        else if (childRB.x == rectRB.x)
        {
            if (g_mousepos.x > m_MousePrePos.x)
            {
                child->position.x = child->position.x + (g_mousepos.x - m_MousePrePos.x);
            }
        }

        //�������ڽ��� �������� ��ڽ��� �������� �ȿ� ������ �� ��ġ ����
        if (childLT.x > rectLT.x)
        {
            gap.x = childLT.x - rectLT.x;

            child->position.x = child->position.x - gap.x;
        }
        //�������ڽ��� �������� ��ڽ��� �������� �ȿ� ������ �� ��ġ ����
        if (childRB.x < rectRB.x)
        {
            gap.x = childRB.x - rectRB.x;

            child->position.x = child->position.x - gap.x;
        }

        //y�൵ �Ȱ��� ����
        if (childLT.y < rectLT.y && childRB.y > rectRB.y)
        {
            child->position.y = child->position.y + (g_mousepos.y - m_MousePrePos.y);
        }
        else if (childLT.y == rectLT.y)
        {
            if (g_mousepos.y < m_MousePrePos.y)
            {
                child->position.y = child->position.y + (g_mousepos.y - m_MousePrePos.y);
            }
        }
        else if (childRB.y == rectRB.y)
        {
            if (g_mousepos.y > m_MousePrePos.y)
            {
                child->position.y = child->position.y + (g_mousepos.y - m_MousePrePos.y);
            }
        }

        if (childLT.y > rectLT.y)
        {
            gap.y = childLT.y - rectLT.y;

            child->position.y = child->position.y - gap.y;
        }
        if (childRB.y < rectRB.y)
        {
            gap.y = childRB.y - rectRB.y;

            child->position.y = child->position.y - gap.y;
        }

        m_MousePrePos = g_mousepos;
    }
}

void ViewBox::OnMouseDown()
{
    m_Isdown = true;
    m_MousePrePos = g_mousepos;
}

void ViewBox::OnMouseUp()
{
    m_Isdown = false;
}

void ViewBox::OnMouseExit()
{
    m_Isdown = false;
}

void ViewBox::OnWheelUp()
{
    Vector2 gap;
    Vector2 childLT, childRB, rectLT, rectRB;

    childLT.x = child->GetScreenPosition().x - (child->size.x * 0.5);   //contentbox������ ��ǥ
    childLT.y = child->GetScreenPosition().y - (child->size.y * 0.5);   //contentbox������ ��ǥ

    childRB.x = child->GetScreenPosition().x + (child->size.x * 0.5);   //contentbox������ ��ǥ
    childRB.y = child->GetScreenPosition().y + (child->size.y * 0.5);   //contentbox������ ��ǥ

    rectLT.x = rect->GetScreenPosition().x - (rect->size.x * 0.5);      //viewbox������ ��ǥ
    rectLT.y = rect->GetScreenPosition().y - (rect->size.y * 0.5);      //viewbox������ ��ǥ

    rectRB.x = rect->GetScreenPosition().x + (rect->size.x * 0.5);      //viewbox������ ��ǥ
    rectRB.y = rect->GetScreenPosition().y + (rect->size.y * 0.5);      //viewbox������ ��ǥ

    if (childRB.y > rectRB.y)
    {
        child->position.y -= 5;
    }

    if (childRB.y < rectRB.y)
    {
        gap.y = childRB.y - rectRB.y;

        child->position.y = child->position.y - gap.y;
    }
}

void ViewBox::OnWheelDown()
{
    Vector2 gap;
    Vector2 childLT, childRB, rectLT, rectRB;

    childLT.x = child->GetScreenPosition().x - (child->size.x * 0.5);   //contentbox������ ��ǥ
    childLT.y = child->GetScreenPosition().y - (child->size.y * 0.5);   //contentbox������ ��ǥ

    childRB.x = child->GetScreenPosition().x + (child->size.x * 0.5);   //contentbox������ ��ǥ
    childRB.y = child->GetScreenPosition().y + (child->size.y * 0.5);   //contentbox������ ��ǥ

    rectLT.x = rect->GetScreenPosition().x - (rect->size.x * 0.5);      //viewbox������ ��ǥ
    rectLT.y = rect->GetScreenPosition().y - (rect->size.y * 0.5);      //viewbox������ ��ǥ

    rectRB.x = rect->GetScreenPosition().x + (rect->size.x * 0.5);      //viewbox������ ��ǥ
    rectRB.y = rect->GetScreenPosition().y + (rect->size.y * 0.5);      //viewbox������ ��ǥ

    if (childLT.y < rectLT.y)
    {
        child->position.y += 5;
    }

    if (childLT.y > rectLT.y)
    {
        gap.y = childLT.y - rectLT.y;

        child->position.y = child->position.y - gap.y;
    }
}

//�巡�׷� �̵�, ���콺 �ٷ� �̵� �Ϸ�
//��ũ�ѹ� �߰��ϱ�, ��ڽ� ���� �Ѿ �̹��� �ڸ��� �ؾ���