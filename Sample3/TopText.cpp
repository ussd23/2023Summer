#include "Scripts.h"

void TopText::Start()
{
    m_Text = GetComponentFromObject(gameObject, TextRenderer);
}

void TopText::Update()
{
    if (m_Text == nullptr) return;

    Minesweeper* Sweeper = GetComponentFromObject(gameObject, Minesweeper);
    Count = Sweeper->GetMineCount();
    if (Sweeper->GetStart() == true) {
        if (Sweeper->GetFinish() == false) {
            Time += Time::deltaTime;
        }
    }
    else {
        Time = 0;
    }

    stringstream temp;
    temp << "ÃÑ Áö·Ú¼ö : " << Count << "   ½Ã°£ : " << Time << "ÃÊ";
    //temp << fixed << setprecision(2) << "[FPS: " << Time::framePerSec << " / AvgFPS: " << Time::avgFrame << "] / Rendered: " << Var::CullingObjects << "\n" << "ÃÑ Áö·Ú¼ö : " << Count << "   ½Ã°£ : " << Time << "ÃÊ";

    m_Text->m_Text = temp.str();
}

