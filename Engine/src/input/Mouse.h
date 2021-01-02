#pragma once

#include "EventArgs.h"

#include <DirectXMath.h>

namespace Ghurund {
    using namespace DirectX;

    enum class MouseButton {
        LEFT, MIDDLE, RIGHT, VIRTUAL
    };

    enum class MouseWheel {
        VERTICAL, HORIZONTAL
    };

    enum class MouseAction {
        DOWN, UP
    };

    class MouseEventArgs:public EventArgs {
    private:
        XMINT2 position;
        bool inside;

    public:
        MouseEventArgs(const XMINT2& pos, uint64_t time, bool inside):EventArgs(time), position(pos), inside(inside) {}

        inline const XMINT2& getPosition() const {
            return position;
        }

        __declspec(property(get = getPosition)) XMINT2& Position;

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
        MouseButtonEventArgs(const XMINT2& pos, MouseAction action, MouseButton button, uint64_t time, bool inside):MouseEventArgs(pos, time, inside) {
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
            XMINT2 childEventPos = { (int32_t)(Position.x + x), (int32_t)(Position.y + y) };
            return MouseButtonEventArgs(childEventPos, action, button, TimeMs, inside);
        }
    };

    class MouseMotionEventArgs:public MouseEventArgs {
    private:
        XMINT2 delta;

    public:
        MouseMotionEventArgs(const XMINT2& pos, const XMINT2& delta, uint64_t time, bool inside):MouseEventArgs(pos, time, inside) {
            this->delta = delta;
        }

        inline const XMINT2& getDelta() const {
            return delta;
        }

        __declspec(property(get = getDelta)) XMINT2& Delta;

        inline MouseMotionEventArgs translate(float x, float y, bool inside) const {
            XMINT2 childEventPos = { (int32_t)(Position.x + x), (int32_t)(Position.y + y) };
            return MouseMotionEventArgs(childEventPos, delta, TimeMs, inside);
        }
    };

    class MouseWheelEventArgs:public MouseEventArgs {
    private:
        MouseWheel wheel;
        int delta;

    public:
        MouseWheelEventArgs(const XMINT2& pos, MouseWheel wheel, int delta, uint64_t time, bool inside):MouseEventArgs(pos, time, inside) {
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
            XMINT2 childEventPos = { (int32_t)(Position.x + x), (int32_t)(Position.y + y) };
            return MouseWheelEventArgs(childEventPos, wheel, delta, TimeMs, Inside);
        }
    };
}