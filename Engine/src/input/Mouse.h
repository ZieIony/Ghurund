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

        virtual ~EventArgs() = 0 {}
    };

    class MouseEventArgs :public EventArgs {
    public:
        MouseEventArgs(time_t time):EventArgs(time) {}
    };

    class MouseButtonEventArgs :public MouseEventArgs {
    private:
        MouseAction action;
        MouseButton button;

    public:
        MouseButtonEventArgs(MouseAction action, MouseButton button, time_t time):MouseEventArgs(time) {
            this->action = action;
            this->button = button;
        }

        MouseAction getAction() {
            return action;
        }

        __declspec(property(get = getAction)) MouseAction Action;

        MouseButton getButton() {
            return button;
        }

        __declspec(property(get = getButton)) MouseButton Button;
    };

    class MouseMotionEventArgs :public MouseEventArgs {
    private:
        XMINT2 delta;

    public:
        MouseMotionEventArgs(XMINT2 &delta, time_t time):MouseEventArgs(time) {
            this->delta = delta;
        }

        const XMINT2 &getDelta() const {
            return delta;
        }

        __declspec(property(get = getDelta)) XMINT2 &Delta;
    };

    class MouseWheelEventArgs :public MouseEventArgs {
    private:
        MouseWheel wheel;
        int delta;

    public:
        MouseWheelEventArgs(MouseWheel wheel, int delta, time_t time):MouseEventArgs(time) {
            this->wheel = wheel;
            this->delta = delta;
        }

        MouseWheel getWheel() {
            return wheel;
        }

        __declspec(property(get = getWheel)) MouseWheel Wheel;

        int getDelta() {
            return delta;
        }

        __declspec(property(get = getDelta)) int Delta;
    };

    struct MouseState {
        ticks_t timeStamp;
        bool buttonPressed[3];
        int position[2];
    };
}