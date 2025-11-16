#pragma once

#include "core/input/InputEventArgs.h"

#include <DirectXMath.h>

namespace Ghurund::Core {
    using namespace ::DirectX;

    class MouseEventArgs:public InputEventArgs {
    private:
        XMINT2 position;
        bool inside;

    public:
        MouseEventArgs(const XMINT2& pos, uint64_t time, bool inside):InputEventArgs(time), position(pos), inside(inside) {}

        inline const XMINT2& getPosition() const {
            return position;
        }

        __declspec(property(get = getPosition)) const XMINT2& Position;

        inline bool isInside() const {
            return inside;
        }

        __declspec(property(get = isInside)) bool Inside;
    };
}