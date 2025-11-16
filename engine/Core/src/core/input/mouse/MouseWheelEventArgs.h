#pragma once

#include "MouseEventArgs.h"

namespace Ghurund::Core {
    enum class MouseWheel {
        VERTICAL, HORIZONTAL
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