#pragma once

#include "Common.h"

namespace Ghurund {

    class InputEventArgs {
    protected:
        uint64_t time;

    public:
        InputEventArgs(uint64_t time) {
            this->time = time;
        }

        inline uint64_t getTimeMs() const {
            return time;
        }

        __declspec(property(get = getTimeMs)) uint64_t TimeMs;

        virtual ~InputEventArgs() = 0 {}
    };
}