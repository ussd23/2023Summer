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
    if (sec == 0) sec = iTime / 1000;

    deltaTime = (iTime - pastTime) / 1000.0f;

    if (sec != iTime / 1000)
    {
        sec = iTime / 1000;
        framePerSec = frames;
        frames = 0;
        avgFrame = passedFrames / (float)++passedTime;
    }

    pastTime = iTime;
}