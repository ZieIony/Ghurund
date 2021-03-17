#pragma once

#include "InputEventArgs.h"

namespace Ghurund::Input {
    enum class KeyAction {
        DOWN, UP, CHAR
    };

    class KeyEventArgs:public InputEventArgs {
    private:
        KeyAction action;
        int key;

    public:
        KeyEventArgs(KeyAction action, int key, uint64_t time):InputEventArgs(time) {
            this->action = action;
            this->key = key;
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