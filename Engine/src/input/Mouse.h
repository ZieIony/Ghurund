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
        int dx, dy;

    public:
        MouseMotionEvent(int dx, int dy, time_t time):MouseEvent(time) {
            this->dx = dx;
            this->dy = dy;
        }

        int getDeltaX() const {
            return dx;
        }

        __declspec(property(get = getDeltaX)) int DeltaX;

        int getDeltaY() const {
            return dy;
        }

        __declspec(property(get = getDeltaY)) int DeltaY;
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
    };

    struct MouseState {
        ticks_t timeStamp;
        bool buttonPressed[3];
        int position[2];
    };
}