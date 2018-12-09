#pragma once

namespace Ghurund {
    enum class MouseButton {
        LEFT, MIDDLE, RIGHT
    };

    enum class MouseWheel {
        VERTICAL, HORIZONTAL
    };

    enum class MouseAction {
        DOWN, UP
    };

    class Event {
    protected:
        time_t time;

    public:
        Event(time_t time) {
            this->time = time;
        }

        virtual ~Event() = 0 {}
    };

    class MouseEvent:public Event {
    public:
        MouseEvent(time_t time):Event(time) {}
    };

    class MouseButtonEvent:public MouseEvent {
    private:
        MouseAction action;
        MouseButton button;

    public:
        MouseButtonEvent(MouseAction action, MouseButton button, time_t time):MouseEvent(time) {
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

    class MouseMotionEvent:public MouseEvent {
    private:
        XMINT2 delta;

    public:
        MouseMotionEvent(XMINT2 &delta, time_t time):MouseEvent(time) {
            this->delta = delta;
        }

        const XMINT2 &getDelta() const {
            return delta;
        }

        __declspec(property(get = getDelta)) XMINT2 &Delta;
    };

    class MouseWheelEvent:public MouseEvent {
    private:
        MouseWheel wheel;
        int delta;

    public:
        MouseWheelEvent(MouseWheel wheel, int delta, time_t time):MouseEvent(time) {
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