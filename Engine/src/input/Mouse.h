#pragma once

namespace Ghurund{
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
        DWORD time;

    public:
        Event(DWORD time) {
            this->time = time;
        }

        virtual ~Event() = 0 {}
    };

    class MouseEvent:public Event {
    public:
        MouseEvent(DWORD time):Event(time) {
        }
    };

    class MouseButtonEvent:public MouseEvent {
    private:
        MouseAction action;
        MouseButton button;

    public:
        MouseButtonEvent(MouseAction action, MouseButton button, DWORD time):MouseEvent(time) {
            this->action = action;
            this->button = button;
        }
    };

    class MouseMotionEvent:public MouseEvent {
    private:
        int x, y;

    public:
        MouseMotionEvent(int x, int y, DWORD time):MouseEvent(time) {
            this->x = x;
            this->y = y;
        }
    };

    class MouseWheelEvent:public MouseEvent {
    private:
        MouseWheel wheel;
        int delta;

    public:
        MouseWheelEvent(MouseWheel wheel, int delta, DWORD time):MouseEvent(time) {
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