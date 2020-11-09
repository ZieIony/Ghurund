#pragma once

#include "application/Timer.h"

namespace Ghurund {
    enum class KeyAction {
        DOWN, UP, CHAR
    };

    class KeyEventArgs {
    private:
        KeyAction action;
        int key;
        int64_t time;

    public:
        KeyEventArgs(KeyAction action, int key, int64_t time) {
            this->action = action;
            this->key = key;
            this->time = time;
        }

        KeyAction getAction() const {
            return action;
        }

        __declspec(property(get = getAction)) KeyAction Action;

        int getKey() const {
            return key;
        }

        __declspec(property(get = getKey)) int Key;

        inline int64_t getTime() const {
            return time;
        }

        __declspec(property(get = getTime)) int64_t Time;
    };
}