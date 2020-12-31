#pragma once

#include "application/Timer.h"
#include "Mouse.h"
#include "core/collection/List.h"
#include "Keyboard.h"
#include "Windowsx.h"
#include "EventConsumer.h"

namespace Ghurund {
    struct WindowMessage {
        unsigned int code;
        WPARAM wParam;
        uint64_t time;
        POINT mousePos;
    };
    
    class SystemWindow;

    class Input {
    private:
        POINT prevMousePos;
        XMINT2 mousePos;
        bool keys[256];
        List<WindowMessage> events;

    public:
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