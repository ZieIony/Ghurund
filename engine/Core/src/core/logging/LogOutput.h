#pragma once

#include "Log.h"

namespace Ghurund::Core {
    class LogOutput {
    public:
        virtual ~LogOutput() = 0 {}

        virtual void log(const Log& log) = 0;
    };
}
