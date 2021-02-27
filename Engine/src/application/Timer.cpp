#include "Timer.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund {
    const Ghurund::Type& Timer::GET_TYPE() {
        static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<Timer>();
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Timer))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

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
        timeMs = (uint32_t)(ticks / (frequency.QuadPart / 1000.0));
        frameTicks = currentFrame.QuadPart - prevFrame.QuadPart;
        frameTime = (float)frameTicks / frequency.QuadPart;
        frameTimeMs = (uint32_t)(ticks / (frequency.QuadPart / 1000.0));
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