#pragma once

#include "Mouse.h"
#include "core/collection/List.h"
#include "Keyboard.h"
#include "EventConsumer.h"
#include "application/WindowMessage.h"

namespace Ghurund {
    class SystemWindow;
}

namespace Ghurund::Input {

    class Input {
    private:
        POINT prevMousePos;
        IntPoint mousePos;
        bool keys[256];
        List<WindowMessage> events;

    public:
        Input() {
            memset(keys, 0, sizeof(bool) * 256);
        }

        inline void addEvent(const WindowMessage& msg) {
            events.add(msg);
        }

        void dispatchEvents(uint64_t time, SystemWindow& window);

        inline bool isShiftDown() {
            return keys[VK_SHIFT];
        }

        inline bool isControlDown() {
            return keys[VK_CONTROL];
        }
    };
}