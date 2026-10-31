#pragma once

#include <Windows.h>
#include "Time.h"

namespace Ghurund::Core {
    class Timer {
    private:
        LARGE_INTEGER frequency;
        double fqMs = 0.0, fqNs = 0.0;
        LARGE_INTEGER startFrame, currentFrame;

        Time<double> appTime = {};
        Time<float> frameTime = {};

        float timeScale = 1, maxFrameTime = 1;
        float fixedFrameTime = 1 / 60.0f;

        float fps = 60, fpsTime = 0.0f;
        uint32_t fpsFrames = 0, frameWindow = 60;

        float frameTimeReminder = 0;

        Timer& operator=(const Timer& other) = delete;

    public:
        Timer();

        /**
        * Updates application time and frame time to the current time.
        **/
        void tick();

        /**
        * Updates step time by the fixed time step. Returns true if the step fits into the current frame, false otherwise.
        **/
        bool step();

        /**
        * Time span between this timer creation and the last timer tick.
        **/
        inline const Time<double>& getApplicationTime() const {
            return appTime;
        }

        /**
        * Time span between this timer creation and the last timer tick.
        **/
        __declspec(property(get = getApplicationTime)) const Time<double>& ApplicationTime;

        /**
        * Time span between the previous timer tick and the last timer tick.
        **/
        inline const Time<float>& getFrameTime() const {
            return frameTime;
        }

        /**
        * Time span between the previous timer tick and the last timer tick.
        **/
        __declspec(property(get = getFrameTime)) const Time<float>& FrameTime;

        inline float getTimeScale() const {
            return timeScale;
        }

        inline void setTimeScale(float timeScale) {
            this->timeScale = timeScale;
        }

        __declspec(property(get = getTimeScale, put = setTimeScale)) float TimeScale;

        inline float getMaxFrameTime() const {
            return maxFrameTime;
        }

        inline void setMaxFrameTime(float maxFrameTime) {
            this->maxFrameTime = maxFrameTime;
        }

        __declspec(property(get = getMaxFrameTime, put = setMaxFrameTime)) float MaxFrameTime;

        inline float getFixedFrameTime() const {
            return fixedFrameTime;
        }

        inline void setFixedFrameTime(float fixedFrameTime) {
            this->fixedFrameTime = fixedFrameTime;
        }

        __declspec(property(get = getFixedFrameTime, put = setFixedFrameTime)) float FixedFrameTime;

        inline float getFrameTimeReminder() const {
            return frameTimeReminder;
        }

        __declspec(property(get = getFrameTimeReminder)) float FrameTimeReminder;

        inline float getFramesPerSecond() const {
            return fps;
        }

        __declspec(property(get = getFramesPerSecond)) float FramesPerSecond;

        /**
        * Frame window is used to calculate FPS - accumulated frame time of frame findow frames is divided by frame window.
        **/
        inline uint32_t getFrameWindow() const {
            return frameWindow;
        }

        /**
        * Frame window is used to calculate FPS - accumulated frame time of frame findow frames is divided by frame window.
        **/
        inline void setFrameWindow(uint32_t frameWindow) {
            this->frameWindow = frameWindow;
        }

        __declspec(property(get = getFrameWindow, put = setFrameWindow)) uint32_t FrameWindow;
    };
}
