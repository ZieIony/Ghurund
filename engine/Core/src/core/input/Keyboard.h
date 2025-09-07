#pragma once

#include "InputEventArgs.h"

namespace Ghurund::Core {
    enum class KeyAction {
        PRESSED, DOWN, RELEASED, CHAR
    };

    class KeyEventArgs:public InputEventArgs {
    private:
        KeyAction action;
        uint8_t keyCode;

    public:
        KeyEventArgs(KeyAction action, uint8_t keyCode, uint64_t time):InputEventArgs(time) {
            this->action = action;
            this->keyCode = keyCode;
        }

        KeyAction getAction() const {
            return action;
        }

        __declspec(property(get = getAction)) KeyAction Action;

        uint8_t getKeyCode() const {
            return keyCode;
        }

        __declspec(property(get = getKeyCode)) uint8_t KeyCode;
    };
}