#pragma once

#include "core/threading/CriticalSection.h"

#include <functional>
#include <queue>

namespace Ghurund {
    class FunctionQueue {
    private:
        std::queue<std::function<void()>> queue;
        CriticalSection section;
        HWND window;
        unsigned int eventCode;

    public:
        FunctionQueue(HWND window, unsigned int eventCode) {
            this->window = window;
            this->eventCode = eventCode;
        }

        unsigned int getEventCode() {
            return eventCode;
        }

        void post(std::function<void()> function) {
            section.enter();
            queue.push(function);
            section.leave();
            PostMessage(window, eventCode, 0, 0);
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