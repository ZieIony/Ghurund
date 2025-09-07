#pragma once

#include "InputEventArgs.h"
#include "core/math/Point.h"

namespace Ghurund::Core {
    class MouseEventArgs:public InputEventArgs {
    private:
        IntPoint position;
        bool inside;

    public:
        MouseEventArgs(const IntPoint& pos, uint64_t time, bool inside):InputEventArgs(time), position(pos), inside(inside) {}

        inline const IntPoint& getPosition() const {
            return position;
        }

        __declspec(property(get = getPosition)) IntPoint& Position;

        inline bool isInside() const {
            return inside;
        }

        __declspec(property(get = isInside)) bool Inside;
    };
}