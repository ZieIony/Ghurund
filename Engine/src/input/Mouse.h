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

        ~MouseButtonEvent() {
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

        ~MouseMotionEvent() {
        }
    };

    class MouseWheelEvent:public MouseEvent {
    public:
        MouseWheelEvent(DWORD time):MouseEvent(time) {
        }

        ~MouseWheelEvent() {
        }
    };
    
    struct MouseState {
        ticks_t timeStamp;
        bool buttonPressed[3];
        int position[2];
    };
}