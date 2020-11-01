#pragma once

#include "core/threading/CriticalSection.h"

#include <functional>
#include <queue>

namespace Ghurund {
    class FunctionQueue {
    private:
        std::queue<std::function<void()>> queue;
        CriticalSection section;

    public:
        void post(std::function<void()> function) {
            section.enter();
            queue.push(function);
            section.leave();
        }

        void invoke() {
            section.enter();
            while (!queue.empty()) {
                std::function<void()> function = queue.front();
                function();
                queue.pop();
            }
            section.leave();
        }
    };
}