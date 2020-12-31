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
            if (function == nullptr) {
                Logger::log(LogType::WARNING, _T("Empty function posted to function queue\n"));
                return;
            }
            section.enter();
            queue.push(function);
            section.leave();
        }

        void invoke() {
            section.enter();
            std::queue<std::function<void()>> copy = queue;
            while (!queue.empty())
                queue.pop();
            section.leave();

            while (!copy.empty()) {
                std::function<void()> function = copy.front();
                function();
                copy.pop();
            }
        }
    };
}