#pragma once

#include "MouseEventArgs.h"
#include "core/math/Point.h"

namespace Ghurund::Core {
    class MouseMotionEventArgs:public MouseEventArgs {
    private:
        IntPoint delta;

    public:
        MouseMotionEventArgs(const IntPoint& pos, const IntPoint& delta, uint64_t time, bool inside):MouseEventArgs(pos, time, inside) {
            this->delta = delta;
        }

        inline const IntPoint& getDelta() const {
            return delta;
        }

        __declspec(property(get = getDelta)) IntPoint& Delta;

        inline MouseMotionEventArgs translate(float x, float y, bool inside) const {
            IntPoint childEventPos = { (int32_t)(Position.x + x), (int32_t)(Position.y + y) };
            return MouseMotionEventArgs(childEventPos, delta, TimeMs, inside);
        }
    };
}