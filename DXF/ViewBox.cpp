#include "ComponentHeader.h"

void ViewBox::Start()
{
    m_Rect = GetComponentFromObject(gameObject, RectTransform);

    //contentbox와 scroll관련 오브젝트들의 recttranceform정보 미리 받아둠
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

        //마우스 위치 저장
        m_MousePrePos = Input::MousePosition;
    }
}

void ViewBox::MoveContentBox()
{
    Vector2 contPos = m_ContentRect->GetPosition();

    Vector2 normal = NormalizePosition(contPos, m_ContentMinRange, m_ContentMaxRange);

    //우향 가동 한계에 도달한경우 왼쪽으로만 움직일 수 있게 함
    if (normal.x == 1)
    {
        if (Input::MousePosition.x < m_MousePrePos.x)
        {
            contPos.x = contPos.x + (Input::MousePosition.x - m_MousePrePos.x);
        }
    }
    //좌향 가동 한계에 도달한경우 오른쪽으로만 움직일 수 있게 함
    else if (normal.x == 0)
    {
        if (Input::MousePosition.x > m_MousePrePos.x)
        {
            contPos.x = contPos.x + (Input::MousePosition.x - m_MousePrePos.x);
        }
    }
    //어느쪽도 아니라면 자유롭게 움직일 수 있게 함
    else
    {
        contPos.x = contPos.x + (Input::MousePosition.x - m_MousePrePos.x);
    }

    //하향 가동 한계에 도달한경우 위쪽으로만 움직일 수 있게 함
    if (normal.y == 1)
    {
        if (Input::MousePosition.y < m_MousePrePos.y)
        {
            contPos.y = contPos.y + (Input::MousePosition.y - m_MousePrePos.y);
        }
    }
    //상향 가동 한계에 도달한경우 아래쪽으로만 움직일 수 있게 함
    else if (normal.y == 0)
    {
        if (Input::MousePosition.y > m_MousePrePos.y)
        {
            contPos.y = contPos.y + (Input::MousePosition.y - m_MousePrePos.y);
        }
    }
    //어느쪽도 아니라면 자유롭게 움직일 수 있게 함
    else
    {
        contPos.y = contPos.y + (Input::MousePosition.y - m_MousePrePos.y);
    }

    //조정된 위치로 다시 한번 정규화
    normal = NormalizePosition(contPos, m_ContentMinRange, m_ContentMaxRange);

    //조정된 위치가 우향 가동 한계를 넘으면 위치를 한계치로 설정
    if (normal.x > 1)
    {
        normal.x = 1;
    }
    //조정된 위치가 좌향 가동 한계를 넘으면 위치를 한계치로 설정
    else if (normal.x < 0)
    {
        normal.x = 0;
    }

    //조정된 위치가 하향 가동 한계를 넘으면 위치를 한계치로 설정
    if (normal.y > 1)
    {
        normal.y = 1;
    }
    //조정된 위치가 상향 가동 한계를 넘으면 위치를 한계치로 설정
    else if (normal.y < 0)
    {
        normal.y = 0;
    }

    //최종 조정된 위치를 콘텐츠박스에 적용
    Vector2 tempPos = DisNormalizePosition(normal, m_ContentMinRange, m_ContentMaxRange);
    m_ContentRect->SetPosition(tempPos);

    //콘텐츠박스의 위치 변경에 맞춰 스크롤바 위치 조정
    UpdateScrollBar();
}

//스크롤바의 위치 변경에 맞춰 콘텐츠 박스 위치 조정
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

//콘텐츠박스의 위치 변경에 맞춰 스크롤바 위치 조정
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

//스크롤바의 가동 영역을 구함
void ViewBox::CalcScrollMovableRange()
{
    //현재 스크롤바 높이/길이 계산
    //스크롤의 상하/좌우 끝 좌표에서 스크롤바 높이/길이 절반만큼 제외 = 가동영역
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

//콘텐츠박스의 가동 영역을 구함
void ViewBox::CalcContentMovableRange()
{
    //뷰박스와 콘텐츠박스의 높이, 길이 계산
    //높이와 길이를 모두 절반으로 나눠서 그 차이를 구하고
    //뷰박스의 위치 기준 +- 구한 차이값이 가동 영역
    if (m_ContentRect != nullptr)
    {
        m_ContentMaxRange.x = (m_ContentRect->m_Size.x - m_Rect->m_Size.x) * 0.5;
        m_ContentMaxRange.y = (m_ContentRect->m_Size.y - m_Rect->m_Size.y) * 0.5;
        m_ContentMinRange.x = -(m_ContentRect->m_Size.x - m_Rect->m_Size.x) * 0.5;
        m_ContentMinRange.y = -(m_ContentRect->m_Size.y - m_Rect->m_Size.y) * 0.5;
    }
}

//가동 영역 내 현재 위치를 0~1사이의 값으로 변환함()
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

    //사이즈가 변했으므로 가동 영역 다시 계산
    CalcScrollMovableRange();
    //가동 영역이 변했으므로 현재 위치 다시 계산
    UpdateScrollBar();
}

//뷰박스의 크기와 콘텐츠박스의 크기의 차이에 따라 스크롤바 크기 조정(0.1~1)
//스크롤바 크기가 1이되면 스크롤 비활성화

//콘텐츠박스에 가동 최고점에 도달하면 사이즈 늘리고 늘린 길이의 절반만큼 내리는 기능 추가

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

    //콘텐츠박스의 위치 변경에 맞춰 스크롤바 위치 조정
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

    //콘텐츠박스의 위치 변경에 맞춰 스크롤바 위치 조정
    UpdateScrollBar();
}