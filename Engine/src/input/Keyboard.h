#pragma once

#include "application/Timer.h"

namespace Ghurund {
    enum class KeyAction {
        DOWN, UP
    };

    class KeyEventArgs {
    private:
        KeyAction action;
        int key;
        ticks_t timeStamp;

    public:
        KeyEventArgs(KeyAction action, int key, ticks_t timeStamp) {
            this->action = action;
            this->key = key;
            this->timeStamp = timeStamp;
        }

        KeyAction getAction() const {
            return action;
        }

        __declspec(property(get = getAction)) KeyAction Action;

        int getKey() const {
            return key;
        }

        __declspec(property(get = getKey)) int Key;
    };
}