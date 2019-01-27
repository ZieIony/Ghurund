#pragma once

#include "Ghurund.h"
#include "collection/AverageValue.h"

namespace Ghurund {
    typedef LONGLONG ticks_t;

    class Timer {
    private:
        LARGE_INTEGER frequency;
        LARGE_INTEGER startFrame;
        LARGE_INTEGER prevFrame, currentFrame;
        bool paused = false;

    public:

        Timer();

        void tick();

        ticks_t getRunTicks()const {
            return currentFrame.QuadPart-startFrame.QuadPart;
        }

        __declspec(property(get = getRunTicks)) ticks_t RunTicks;

        float getRunTime()const {
            return (float)getRunTicks()/frequency.QuadPart;
        }

        __declspec(property(get = getRunTime)) float RunTime;

        ticks_t getFrameTicks()const {
            return currentFrame.QuadPart-prevFrame.QuadPart;
        }

        __declspec(property(get = getFrameTicks)) ticks_t FrameTicks;

        float getFrameTime()const {
            return (float)getFrameTicks()/frequency.QuadPart;
        }

        __declspec(property(get = getFrameTime)) float FrameTime;

        void setPaused(bool p = true);

        bool isPaused() {
            return paused;
        }

        __declspec(property(put = setPaused, get = isPaused)) bool Paused;
    };
}