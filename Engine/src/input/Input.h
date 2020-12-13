#pragma once

#include "application/Timer.h"
#include "Mouse.h"
#include "core/collection/List.h"
#include "Keyboard.h"
#include "Windowsx.h"
#include "EventConsumer.h"
#include "application/SystemWindow.h"

namespace Ghurund {
    class Input {
    private:
        List<WindowMessage> messages;
        XMINT2 mousePos;
        bool keys[256];

        bool dispatchEvent(const WindowMessage& message, EventDispatcher& consumer);

    public:
        void dispatchMessage(WindowMessage& message) {
            messages.add(message);
        }

        void dispatchEvents(EventDispatcher& consumer) {
            for (size_t i = 0; i < messages.Size;) {
                if (dispatchEvent(messages[i], consumer)) {
                    messages.removeAt(i);
                } else {
                    i++;
                }
            }
        }

        void clearEvents() {
            messages.clear();
        }

        XMINT2 getMousePos() const {
            return mousePos;
        }

        __declspec(property(get = getMousePos)) XMINT2 MousePos;

        const bool* getKeys() const {
            return keys;
        }

        __declspec(property(get = getKeys)) bool* Keys;

        static inline bool isShiftDown() {
            return (GetKeyState(VK_SHIFT) & 0x80) != 0;
        }

        static inline bool isControlDown() {
            return (GetKeyState(VK_CONTROL) & 0x80) != 0;
        }
    };
}