#pragma once

#include "MouseEventArgs.h"
#include "core/math/Point.h"

namespace Ghurund::Core {
    class MouseMotionEventArgs:public MouseEventArgs {
    private:
        XMINT2 delta;

    public:
        MouseMotionEventArgs(const XMINT2& pos, const XMINT2& delta, uint64_t time, bool inside):MouseEventArgs(pos, time, inside) {
            this->delta = delta;
        }

        inline const XMINT2& getDelta() const {
            return delta;
        }

        __declspec(property(get = getDelta)) const XMINT2& Delta;

        inline MouseMotionEventArgs translate(float x, float y, bool inside) const {
            XMINT2 childEventPos = { (int32_t)(Position.x + x), (int32_t)(Position.y + y) };
            return MouseMotionEventArgs(childEventPos, delta, TimeMs, inside);
        }
    };
}