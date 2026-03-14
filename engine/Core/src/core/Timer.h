#pragma once

#include <cstdint>
#include <Windows.h>

namespace Ghurund::Core {
    class Timer {
    private:
        LARGE_INTEGER frequency;
        double fqMs = 0.0, fqNs = 0.0;
        LARGE_INTEGER startFrame, currentFrame;

        double time = 0.0;
        float frameTime = 0.0f;
        uint32_t timeMs = 0, frameTimeMs = 0;
        uint64_t timeNs = 0, frameTimeNs = 0;

        double scaledTime = 0.0;
        float scaledFrameTime = 0.0f;
        float timeScale = 1, maxFrameTime = 1;
        float fixedFrameTime = 1 / 60.0f;

        float fps = 60, fpsTime = 0.0f;
        uint32_t fpsFrames = 0, frameWindow = 60;

        Timer& operator=(const Timer& other) = delete;

    public:
        Timer();

        void tick();

        inline double getTime() const {
            return time;
        }

        __declspec(property(get = getTime)) double Time;

        inline uint32_t getTimeMs() const {
            return timeMs;
        }

        __declspec(property(get = getTimeMs)) uint32_t TimeMs;

        inline uint64_t getTimeNs() const {
            return timeNs;
        }

        __declspec(property(get = getTimeNs)) uint64_t TimeNs;

        inline float getFrameTime() const {
            return frameTime;
        }

        __declspec(property(get = getFrameTime)) float FrameTime;

        inline uint32_t getFrameTimeMs() const {
            return frameTimeMs;
        }

        __declspec(property(get = getFrameTimeMs)) uint32_t FrameTimeMs;

        inline uint64_t getFrameTimeNs() const {
            return frameTimeNs;
        }

        __declspec(property(get = getFrameTimeNs)) uint64_t FrameTimeNs;

        /**
        * Scaled time takes max frame time into account,
        * so scaled time may not be equal to time even if time scale == 1.
        **/
        inline double getScaledTime() const {
            return scaledTime;
        }

        __declspec(property(get = getScaledTime)) double ScaledTime;

        /**
        * Scaled frame time takes max frame time into account,
        * so scaled frame time may not be equal to frame time even if time scale == 1.
        **/
        inline float getScaledFrameTime() const {
            return scaledFrameTime;
        }

        __declspec(property(get = getScaledFrameTime)) float ScaledFrameTime;

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
