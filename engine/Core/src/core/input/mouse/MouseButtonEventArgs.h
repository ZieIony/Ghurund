#pragma once

#include "MouseEventArgs.h"

namespace Ghurund::Core {
    enum class MouseButton {
        LEFT, MIDDLE, RIGHT, VIRTUAL
    };

    enum class MouseButtonAction {
        PRESSED, DOWN, RELEASED
    };

    class MouseButtonEventArgs:public MouseEventArgs {
    private:
        MouseButtonAction action;
        MouseButton button;
        uint64_t pressedDuration;

    public:
        MouseButtonEventArgs(const XMINT2& pos, MouseButtonAction action, MouseButton button, uint64_t pressedDuration, uint64_t time, bool inside):
            MouseEventArgs(pos, time, inside),
            action(action),
            button(button),
            pressedDuration(pressedDuration){
        }

        inline MouseButtonAction getAction() const {
            return action;
        }

        __declspec(property(get = getAction)) MouseButtonAction Action;

        inline MouseButton getButton() const {
            return button;
        }

        __declspec(property(get = getButton)) MouseButton Button;

        inline uint64_t getPressedDurationMs() const {
            return pressedDuration;
        }

        __declspec(property(get = getPressedDuration)) uint64_t PressedDurationMs;

        inline MouseButtonEventArgs translate(float x, float y, bool inside) const {
            XMINT2 childEventPos = { (int32_t)(Position.x + x), (int32_t)(Position.y + y) };
            return MouseButtonEventArgs(childEventPos, action, button, pressedDuration, TimeMs, inside);
        }
    };
}