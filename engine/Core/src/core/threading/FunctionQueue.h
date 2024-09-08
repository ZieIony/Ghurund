#pragma once

#include "core/threading/CriticalSection.h"

#include <queue>

namespace Ghurund::Core {
    class FunctionQueue {
    private:
        std::queue<std::function<void()>> queue;
        CriticalSection section;

    public:
        void post(std::function<void()> function);

        void invoke();
    };
}