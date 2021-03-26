#pragma once

#include "InputEventArgs.h"
#include "core/math/Point.h"

namespace Ghurund {
    enum class MouseButton {
        LEFT, MIDDLE, RIGHT, VIRTUAL
    };

    enum class MouseWheel {
        VERTICAL, HORIZONTAL
    };

    enum class MouseAction {
        DOWN, UP
    };

    class MouseEventArgs:public InputEventArgs {
    private:
        IntPoint position;
        bool inside;

    public:
        MouseEventArgs(const IntPoint& pos, uint64_t time, bool inside):InputEventArgs(time), position(pos), inside(inside) {}

        inline const IntPoint& getPosition() const {
            return position;
        }

        __declspec(property(get = getPosition)) IntPoint& Position;

        inline bool isInside() const {
            return inside;
        }

        __declspec(property(get = isInside)) bool Inside;
    };

    class MouseButtonEventArgs:public MouseEventArgs {
    private:
        MouseAction action;
        MouseButton button;

    public:
        MouseButtonEventArgs(const IntPoint& pos, MouseAction action, MouseButton button, uint64_t time, bool inside):MouseEventArgs(pos, time, inside) {
            this->action = action;
            this->button = button;
        }

        inline MouseAction getAction() const {
            return action;
        }

        __declspec(property(get = getAction)) MouseAction Action;

        inline MouseButton getButton() const {
            return button;
        }

        __declspec(property(get = getButton)) MouseButton Button;

        inline MouseButtonEventArgs translate(float x, float y, bool inside) const {
            IntPoint childEventPos = { (int32_t)(Position.x + x), (int32_t)(Position.y + y) };
            return MouseButtonEventArgs(childEventPos, action, button, TimeMs, inside);
        }
    };

    class MouseMotionEventArgs:public MouseEventArgs {
    private:
        IntPoint delta;

    public:
        MouseMotionEventArgs(const IntPoint& pos, const IntPoint& delta, uint64_t time, bool inside):MouseEventArgs(pos, time, inside) {
            this->delta = delta;
        }

        inline const IntPoint& getDelta() const {
            return delta;
        }

        __declspec(property(get = getDelta)) IntPoint& Delta;

        inline MouseMotionEventArgs translate(float x, float y, bool inside) const {
            IntPoint childEventPos = { (int32_t)(Position.x + x), (int32_t)(Position.y + y) };
            return MouseMotionEventArgs(childEventPos, delta, TimeMs, inside);
        }
    };

    class MouseWheelEventArgs:public MouseEventArgs {
    private:
        MouseWheel wheel;
        int delta;

    public:
        MouseWheelEventArgs(const IntPoint& pos, MouseWheel wheel, int delta, uint64_t time, bool inside):MouseEventArgs(pos, time, inside) {
            this->wheel = wheel;
            this->delta = delta;
        }

        inline MouseWheel getWheel() const {
            return wheel;
        }

        __declspec(property(get = getWheel)) MouseWheel Wheel;

        inline int getDelta() const {
            return delta;
        }

        __declspec(property(get = getDelta)) int Delta;

        inline MouseWheelEventArgs translate(float x, float y) const {
            IntPoint childEventPos = { (int32_t)(Position.x + x), (int32_t)(Position.y + y) };
            return MouseWheelEventArgs(childEventPos, wheel, delta, TimeMs, Inside);
        }
    };
}