#pragma once

#include "core/Pointer.h"
#include "input/EventConsumer.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"

namespace Ghurund {
    class Control:public Pointer, public EventConsumer {
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