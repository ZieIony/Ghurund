#pragma once

#include "Mouse.h"
#include "core/collection/List.h"
#include "Keyboard.h"
#include "EventConsumer.h"
#include "core/window/WindowMessage.h"

namespace Ghurund::Core {

    class Input {
    private:
        POINT prevMousePos = {};
        IntPoint mousePos = { 0,0 };
        bool keys[256];
        List<WindowMessage> events;

    public:
        Input() {
            memset(keys, 0, sizeof(bool) * 256);
        }

        inline void addEvent(const WindowMessage& msg) {
            events.add(msg);
        }

        void dispatchEvents(uint64_t time, EventConsumer& consumer);

        inline bool isShiftDown() {
            return keys[VK_SHIFT];
        }

        inline bool isControlDown() {
            return keys[VK_CONTROL];
        }
    };
}