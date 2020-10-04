#pragma once

#include <time.h>
#include <algorithm>
#include <functional>

namespace Ghurund::UI {
    class Animation {
    private:
        unsigned long duration = 200;
        time_t startTime = 0;
        std::function<void(float)> onProgressChanged;

    public:
        Animation(std::function<void(float)> onProgressChanged) {
            this->onProgressChanged = onProgressChanged;
        }

        void start() {
            if (!Started) {
                startTime = time(0);
                onProgressChanged(Progress);
            }
        }

        void update() {
            if (Started && !Finished) {
                onProgressChanged(Progress);
            }
        }

        void finish() {
            if (!Finished) {
                startTime = time(0) - duration;
                onProgressChanged(Progress);
            }
        }

        inline float getProgress() const {
            return std::max(0.0f, std::min((float)(time(0) - startTime) / duration, 1.0f));
        }

        __declspec(property(get = getProgress)) float Progress;

        inline bool isStarted() const {
            return startTime > 0 && time(0) <= startTime + duration;
        }

        __declspec(property(get = isStarted)) bool Started;

        inline bool isFinished() const {
            return startTime > 0 && time(0) > startTime + duration;
        }

        __declspec(property(get = isFinished)) bool Finished;

        inline unsigned long getDuration()const {
            return duration;
        }

        inline void setDuration(unsigned long duration) {
            this->duration = duration;
        }

        __declspec(property(get = getDuration, put = setDuration)) unsigned long Duration;
    };
}