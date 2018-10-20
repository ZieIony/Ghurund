#pragma once

#include "core/Timer.h"

namespace Ghurund {
    enum class KeyAction {
        DOWN, UP
    };

    class KeyEvent {
    private:
        KeyAction action;
        int key;
        ticks_t timeStamp;

    public:
        KeyEvent(KeyAction action, int key, ticks_t timeStamp) {
            this->action = action;
            this->key = key;
            this->timeStamp = timeStamp;
        }

        KeyAction getAction() {
            return action;
        }

        __declspec(property(get = getAction)) KeyAction Action;

        int getKey() {
            return key;
        }

        __declspec(property(get = getKey)) int Key;
    };
}