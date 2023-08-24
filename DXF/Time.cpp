#include "DXHeader.h"
#include "Global.h"

UINT Time::pastTime = 0;
int Time::sec = 0;
int Time::frames = 0;
int Time::passedFrames = 0;
int Time::passedTime = 0;
FLOAT Time::deltaTime = 0;
int	  Time::framePerSec = 0;
float Time::avgFrame = 0;

void Time::TimeUpdate()
{
    ++frames;
    ++passedFrames;

    UINT iTime = GetTickCount64();

    if (pastTime == 0) pastTime = iTime;
    int time = iTime / 1000;
    if (sec == 0) sec = time;

    deltaTime = (iTime - pastTime) * 0.001f;

    if (sec != time)
    {
        sec = time;
        framePerSec = frames;
        frames = 0;
        avgFrame = passedFrames / (float)++passedTime;
    }

    pastTime = iTime;
}