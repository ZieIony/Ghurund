#include "Timer.h"

namespace Ghurund {
    Timer::Timer():fps(AverageValue<float>(100)) {
        QueryPerformanceCounter(&startFrame);
        startTime = GetTickCount();
        prevFrame = currentFrame = startFrame;
        QueryPerformanceFrequency(&frequency);
    }

    void Timer::tick() {
        if(paused)
            return;

        prevFrame = currentFrame;
        QueryPerformanceCounter(&currentFrame);
        float frameTime = (float)(currentFrame.QuadPart-prevFrame.QuadPart)/frequency.QuadPart;
        if(frameTime!=0)
            fps.set(1.0f/frameTime);
    }

    void Timer::setPaused(bool p)const {
        if(paused==p)
            return;

        /*if(p) {
            LARGE_INTEGER currentTicks;
            QueryPerformanceCounter(&currentTicks);
            frameTime = (float)(currentTicks.QuadPart-frameDelay.QuadPart)/(float)frequency.QuadPart;
            if(frameTime!=0)
                fps.set(1.0f/frameTime);
            time += frameTime;
        } else {
            QueryPerformanceCounter(&frameDelay);
        }*/

        paused = p;
    }
}