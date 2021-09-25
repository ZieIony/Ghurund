#pragma once

#include "core/Event.h"

#include <algorithm>

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class Animation {
    private:
        uint64_t duration = 200;
        uint64_t startTime = 0, currentTime;
        Event<Animation> progressChanged = Event<Animation>(*this);
        bool running = false;

    public:
        void start() {
            startTime = 0;
            running = true;
        }

        void update(uint64_t time) {
            if (!Running)
                return;
            if (startTime == 0)
                startTime = time;
            currentTime = time;
            progressChanged();
            if (Finished)
                running = false;
        }

        void finish() {
            if (!Finished) {
                startTime = currentTime - duration;
                progressChanged();
            }
        }

        Event<Animation>& getProgressChanged() {
            return progressChanged;
        }

        __declspec(property(get = getProgressChanged)) Event<Animation>& ProgressChanged;

        inline float getProgress() const {
            return std::max(0.0f, std::min((float)(currentTime - startTime) / duration, 1.0f));
        }

        __declspec(property(get = getProgress)) float Progress;

        inline bool isRunning() const {
            return running;
        }

        __declspec(property(get = isRunning)) bool Running;

        inline bool isFinished() const {
            return running && currentTime > startTime + duration;
        }

        __declspec(property(get = isFinished)) bool Finished;

        inline uint64_t getDuration() const {
            return duration;
        }

        inline void setDuration(uint64_t duration) {
            this->duration = duration;
        }

        __declspec(property(get = getDuration, put = setDuration)) uint64_t Duration;
    };
}