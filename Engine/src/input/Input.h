#pragma once

#include "application/Timer.h"
#include "Mouse.h"
#include "core/collection/List.h"
#include "Keyboard.h"
#include "Windowsx.h"
#include "EventConsumer.h"
#include "application/WindowProc.h"

namespace Ghurund {
    class Input {
    private:
        List<SystemMessage> messages;
        XMINT2 mousePos;
        bool keys[256];

        bool dispatchEvent(const SystemMessage& message, EventDispatcher& consumer);

    public:
        void dispatchMessage(SystemMessage &message) {
            messages.add(message);
        }

        void dispatchEvents(EventDispatcher &consumer) {
            for(size_t i = 0; i < messages.Size;) {
                if(dispatchEvent(messages[i], consumer)) {
                    messages.removeAtKeepOrder(i);
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

        const bool *getKeys() const {
            return keys;
        }

        __declspec(property(get = getKeys)) bool *Keys;
    };
}