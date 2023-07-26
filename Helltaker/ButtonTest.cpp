#include "Scripts.h"
#include "CallFunc.h"

void ButtonTest::func1()
{
    MessageBox(NULL, "OnMouseDown() ½ÇÇàµÊ", "ButtonTest", MB_OK);
}

void ButtonTest::OnMouseDown()
{
    EventManager* mgr = new EventManager();
    mgr->Instance(new CallFunc(func1, 2));
    mgr->Update();
}
