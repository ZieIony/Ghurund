#pragma once

#include <queue>
#include "CriticalSection.h"
#include "Ghurund.h"
#include <functional>

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

        std::function<void()> take() {
            section.enter();
            std::function<void()> function = queue.front();
            queue.pop();
            section.leave();
            return function;
        }
    };
}