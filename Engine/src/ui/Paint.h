#pragma once

#include "Font.h"
#include "core/string/String.h"

namespace Ghurund {
    class Paint {
    private:
        unsigned int color = 0xffffffff;

    public:
        inline unsigned int getColor() const {
            return color;
        }

        inline void setColor(unsigned int color) {
            this->color = color;
        }

        __declspec(property(get = getColor, put = setColor)) unsigned int Color;
    };
}