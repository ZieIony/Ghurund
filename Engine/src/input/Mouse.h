#pragma once

#include "DirectXMath.h"

namespace Ghurund {
    using namespace DirectX;

    enum class MouseButton {
        LEFT, MIDDLE, RIGHT
    };

    enum class MouseWheel {
        VERTICAL, HORIZONTAL
    };

    enum class MouseAction {
        DOWN, UP
    };

    class EventArgs {
    protected:
        time_t time;

    public:
        EventArgs(time_t time) {
            this->time = time;
        }

        inline time_t getTime() const {
            return time;
        }

        __declspec(property(get = getTime)) time_t Time;

        virtual ~EventArgs() = 0 {}
    };

    class MouseEventArgs :public EventArgs {
    private:
        XMINT2 position;

    public:
        MouseEventArgs(const XMINT2& pos, time_t time):EventArgs(time), position(pos) {}

        const XMINT2& getPosition() const {
            return position;
        }

        __declspec(property(get = getPosition)) XMINT2& Position;
    };

    class MouseButtonEventArgs :public MouseEventArgs {
    private:
        MouseAction action;
        MouseButton button;

    public:
        MouseButtonEventArgs(const XMINT2& pos, MouseAction action, MouseButton button, time_t time):MouseEventArgs(pos, time) {
            this->action = action;
            this->button = button;
        }

        MouseAction getAction() const {
            return action;
        }

        __declspec(property(get = getAction)) MouseAction Action;

        MouseButton getButton() const {
            return button;
        }

        __declspec(property(get = getButton)) MouseButton Button;

        MouseButtonEventArgs translate(float x, float y) const {
            XMINT2 childEventPos = { (int32_t)(Position.x + x), (int32_t)(Position.y + y) };
            return MouseButtonEventArgs(childEventPos, action, button, Time);
        }
    };

    class MouseMotionEventArgs :public MouseEventArgs {
    private:
        XMINT2 delta;

    public:
        MouseMotionEventArgs(const XMINT2& pos, const XMINT2 &delta, time_t time):MouseEventArgs(pos, time) {
            this->delta = delta;
        }

        const XMINT2 &getDelta() const {
            return delta;
        }

        __declspec(property(get = getDelta)) XMINT2 &Delta;

        MouseMotionEventArgs translate(float x, float y) const {
            XMINT2 childEventPos = { (int32_t)(Position.x + x), (int32_t)(Position.y + y) };
            return MouseMotionEventArgs(childEventPos, delta, Time);
        }
    };

    class MouseWheelEventArgs :public MouseEventArgs {
    private:
        MouseWheel wheel;
        int delta;

    public:
        MouseWheelEventArgs(const XMINT2& pos, MouseWheel wheel, int delta, time_t time):MouseEventArgs(pos, time) {
            this->wheel = wheel;
            this->delta = delta;
        }

        MouseWheel getWheel() const {
            return wheel;
        }

        __declspec(property(get = getWheel)) MouseWheel Wheel;

        int getDelta() const {
            return delta;
        }

        __declspec(property(get = getDelta)) int Delta;

        MouseWheelEventArgs translate(float x, float y) const {
            XMINT2 childEventPos = { (int32_t)(Position.x + x), (int32_t)(Position.y + y) };
            return MouseWheelEventArgs(childEventPos, wheel, delta, Time);
        }
    };

    struct MouseState {
        ticks_t timeStamp;
        bool buttonPressed[3];
        int position[2];
    };
}