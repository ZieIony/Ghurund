#include "Timer.h"

namespace Ghurund {
    const Ghurund::Type& Timer::TYPE = Ghurund::Type([]() {return ghnew Timer(); }, "Timer");
 
    Timer::Timer() {
        QueryPerformanceCounter(&startFrame);
        QueryPerformanceFrequency(&frequency);
    }

    void Timer::tick() {
        if(paused)
            return;

        prevFrame = currentFrame;
        QueryPerformanceCounter(&currentFrame);
    }

    void Timer::setPaused(bool p) {
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