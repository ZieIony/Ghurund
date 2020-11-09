#include "Timer.h"

namespace Ghurund {
    Timer::Timer() {
        QueryPerformanceCounter(&startFrame);
        QueryPerformanceFrequency(&frequency);
    }

    void Timer::tick() {
        if (paused)
            return;

        LARGE_INTEGER prevFrame = currentFrame;
        QueryPerformanceCounter(&currentFrame);
        ticks = currentFrame.QuadPart - startFrame.QuadPart;
        time = (double)ticks / frequency.QuadPart;
        timeMs = ticks / (frequency.QuadPart / 1000.0);
        frameTicks = currentFrame.QuadPart - prevFrame.QuadPart;
        frameTime = (float)frameTicks / frequency.QuadPart;
        frameTimeMs = ticks / (frequency.QuadPart / 1000.0);
    }

    void Timer::setPaused(bool p) {
        if (paused == p)
            return;

        paused = p;
        if (paused) {
            pauseFrame = currentFrame;
        } else {
            LARGE_INTEGER prevFrame = currentFrame;
            QueryPerformanceCounter(&currentFrame);
            currentFrame.QuadPart -= (prevFrame.QuadPart - pauseFrame.QuadPart);
        }
    }
}