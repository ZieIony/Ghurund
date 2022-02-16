#pragma once

#include "core/Pointer.h"

#include <Windows.h>

namespace Ghurund::Core {
    typedef LONGLONG ticks_t;

    class Timer:public Object {
    private:
        LARGE_INTEGER frequency;
        LARGE_INTEGER startFrame;
        LARGE_INTEGER currentFrame, pauseFrame;
        bool paused = false;
        ticks_t ticks = 0, frameTicks = 0;
        double time = 0.0f, frameTime = 0.0f;
        uint64_t timeMs, frameTimeMs;

    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        Timer();

        void tick();

        ticks_t getTicks() const {
            return ticks;
        }

        __declspec(property(get = getTicks)) ticks_t Ticks;

        ticks_t getFrequency() const {
            return frequency.QuadPart;
        }

        __declspec(property(get = getFrequency)) ticks_t Frequency;

        double getTime()const {
            return time;
        }

        __declspec(property(get = getTime)) double Time;

        uint64_t getTimeMs() const {
            return timeMs;
        }

        __declspec(property(get = getTimeMs)) uint64_t TimeMs;

        ticks_t getFrameTicks() const {
            return frameTicks;
        }

        __declspec(property(get = getFrameTicks)) ticks_t FrameTicks;

        double getFrameTime() const {
            return frameTime;
        }

        __declspec(property(get = getFrameTime)) double FrameTime;

        uint64_t getFrameTimeMs() const {
            return frameTimeMs;
        }

        __declspec(property(get = getFrameTimeMs)) uint64_t FrameTimeMs;

        void setPaused(bool p = true);

        bool isPaused() {
            return paused;
        }

        __declspec(property(put = setPaused, get = isPaused)) bool Paused;

        static const Ghurund::Core::Type& GET_TYPE();
    };
}