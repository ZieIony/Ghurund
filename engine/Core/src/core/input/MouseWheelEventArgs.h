#pragma once

#include "MouseEventArgs.h"
#include "core/math/Point.h"

namespace Ghurund::Core {
    enum class MouseWheel {
        VERTICAL, HORIZONTAL
    };
    
    class MouseWheelEventArgs:public MouseEventArgs {
    private:
        MouseWheel wheel;
        int delta;

    public:
        MouseWheelEventArgs(const IntPoint& pos, MouseWheel wheel, int delta, uint64_t time, bool inside):MouseEventArgs(pos, time, inside) {
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
            IntPoint childEventPos = { (int32_t)(Position.x + x), (int32_t)(Position.y + y) };
            return MouseWheelEventArgs(childEventPos, wheel, delta, TimeMs, Inside);
        }
    };
}