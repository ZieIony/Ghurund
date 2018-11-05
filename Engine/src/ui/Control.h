#pragma once

#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "core/Pointer.h"

namespace Ghurund {
    class Control:public Pointer {
    protected:
        XMFLOAT3 pos, rotation;
        XMFLOAT2 size;

    public:
        virtual void setSize(float width, float height) {
            size.x = abs(width);
            size.y = abs(height);
        }

    };
}