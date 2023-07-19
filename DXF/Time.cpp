#include "DXHeader.h"

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