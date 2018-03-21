#pragma once

#include "Ghurund.h"
#include "collection/AverageValue.h"

namespace Ghurund {
    typedef LONGLONG ticks_t;

    class Timer {
    private:
        LARGE_INTEGER frequency;
        mutable LARGE_INTEGER prevFrame;
        LARGE_INTEGER startFrame;
        DWORD startTime;
        mutable LARGE_INTEGER currentFrame;
        mutable bool paused;

        mutable AverageValue<float> fps;

    public:

        Timer();

        void tick();

        ticks_t getCurrentTicks()const {
            LARGE_INTEGER currentTime;
            QueryPerformanceCounter(&currentTime);
            return currentTime.QuadPart;
        }

        __declspec(property(get = getCurrentTicks)) ticks_t CurrentTicks;

        ticks_t getRunTicks()const {
            return startFrame.QuadPart-currentFrame.QuadPart;
        }

        float getRunTime()const {
            return (float)getRunTicks()/frequency.QuadPart;
        }

        __declspec(property(get = getRunTicks)) ticks_t RunTicks;

        float getFps() {
            return fps.get();
        }

        __declspec(property(get = getFps)) float Fps;

        void setPaused(bool p = true)const;

        bool isPaused() {
            return paused;
        }

        __declspec(property(put = setPaused, get = isPaused)) bool Paused;
    };
}