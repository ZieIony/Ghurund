#pragma once

#include "MouseEventArgs.h"
#include "core/math/Point.h"

namespace Ghurund::Core {
    enum class MouseButton {
        LEFT, MIDDLE, RIGHT, VIRTUAL
    };

    enum class MouseAction {
        PRESSED, RELEASED
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
}