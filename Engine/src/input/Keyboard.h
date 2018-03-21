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

        ~KeyEvent() {
        }

        KeyAction getAction() {
            return action;
        }

        int getKey() {
            return key;
        }
    };
}