#pragma once

#include "Common.h"

namespace Ghurund::Input {

    class EventArgs {
    protected:
        uint64_t time;

    public:
        EventArgs(uint64_t time) {
            this->time = time;
        }

        inline uint64_t getTimeMs() const {
            return time;
        }

        __declspec(property(get = getTimeMs)) uint64_t TimeMs;

        virtual ~EventArgs() = 0 {}
    };
}