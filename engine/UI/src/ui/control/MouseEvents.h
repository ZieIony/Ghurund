#pragma once

#include "core/input/Mouse.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class MousePressed {
        bool pressed[4] = { false, false, false, false };

    public:
        MousePressed() {}

        MousePressed(const MousePressed& other) {
            pressed[0] = other.pressed[0];
            pressed[1] = other.pressed[1];
            pressed[2] = other.pressed[2];
            pressed[3] = other.pressed[3];
        }

        operator bool() const {
            return pressed[0] || pressed[1] || pressed[2] || pressed[3];
        }

        bool& operator[](MouseButton button) {
            return pressed[(unsigned int)button];
        }

        const bool& operator[](MouseButton button) const {
            return pressed[(unsigned int)button];
        }

        bool operator==(const MousePressed& other) const {
            return pressed[0] == other.pressed[0] &&
                pressed[1] == other.pressed[1] &&
                pressed[2] == other.pressed[2] &&
                pressed[3] == other.pressed[3];
        }

        inline void clear() {
            pressed[0] = false;
            pressed[1] = false;
            pressed[2] = false;
            pressed[3] = false;
        }
    };

    class MousePressedEventArgs:public MouseEventArgs {
    private:
        MouseButton button;

    public:
        MousePressedEventArgs(const Ghurund::Core::IntPoint& pos, MouseButton button, uint64_t time):MouseEventArgs(pos, time, true) {
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
        MouseClickedEventArgs(const Ghurund::Core::IntPoint& pos, MouseButton button, uint64_t time, bool inside):MouseEventArgs(pos, time, inside) {
            this->button = button;
        }

        MouseButton getButton() const {
            return button;
        }

        __declspec(property(get = getButton)) MouseButton Button;
    };
}