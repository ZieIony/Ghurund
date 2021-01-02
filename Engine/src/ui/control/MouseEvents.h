#pragma once

#include "input/Mouse.h"

namespace Ghurund::UI {
    using namespace Ghurund::Input;

    class MousePressed {
        bool pressed[4] = { false, false, false, false };

    public:
        operator bool() const {
            return pressed[0] || pressed[1] || pressed[2] || pressed[3];
        }

        bool& operator[](MouseButton button) {
            return pressed[(unsigned int)button];
        }

        const bool& operator[](MouseButton button) const {
            return pressed[(unsigned int)button];
        }
    };

    class MousePressedEventArgs:public MouseEventArgs {
    private:
        MouseButton button;

    public:
        MousePressedEventArgs(const IntPoint& pos, MouseButton button, uint64_t time):MouseEventArgs(pos, time, true) {
            this->button = button;
        }

        MouseButton getButton() const {
            return button;
        }

        __declspec(property(get = getButton)) MouseButton Button;
    };

    class MouseClickedEventArgs:public MouseEventArgs {
    private:
        MouseButton button;

    public:
        MouseClickedEventArgs(const IntPoint& pos, MouseButton button, uint64_t time, bool inside):MouseEventArgs(pos, time, inside) {
            this->button = button;
        }

        MouseButton getButton() const {
            return button;
        }

        __declspec(property(get = getButton)) MouseButton Button;
    };
}