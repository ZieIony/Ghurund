#pragma once

#include "core/collection/AverageValue.h"
#include "core/Pointer.h"

namespace Ghurund {
    typedef LONGLONG ticks_t;

    class Timer:public Object {
    private:
		inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<Timer>();
		
		LARGE_INTEGER frequency;
        LARGE_INTEGER startFrame;
        LARGE_INTEGER prevFrame, currentFrame;
        bool paused = false;

    public:

        Timer();

        void tick();

        ticks_t getTicks()const {
            return currentFrame.QuadPart - startFrame.QuadPart;
        }

        __declspec(property(get = getTicks)) ticks_t Ticks;

        ticks_t getFrequency()const {
            return frequency.QuadPart;
        }

        __declspec(property(get = getFrequency)) ticks_t Frequency;

        float getTime()const {
            float f = (float)getTicks() / frequency.QuadPart;
            return f;
        }

        __declspec(property(get = getTime)) float Time;

        ticks_t getFrameTicks()const {
            return currentFrame.QuadPart - prevFrame.QuadPart;
        }

        __declspec(property(get = getFrameTicks)) ticks_t FrameTicks;

        float getFrameTime()const {
            return (float)getFrameTicks() / frequency.QuadPart;
        }

        __declspec(property(get = getFrameTime)) float FrameTime;

        void setPaused(bool p = true);

        bool isPaused() {
            return paused;
        }

        __declspec(property(put = setPaused, get = isPaused)) bool Paused;

        inline static const Ghurund::Type& TYPE = Ghurund::Type(CONSTRUCTOR, "Ghurund", "Timer");

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}