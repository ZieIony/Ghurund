#pragma once

#include "core/string/String.h"

namespace Ghurund::UI {
    class Paint {
    private:
        unsigned int color = 0xffffffff;
        float thickness = 1.0f;

    public:
        inline unsigned int getColor() const {
            return color;
        }

        inline void setColor(unsigned int color) {
            this->color = color;
        }

        __declspec(property(get = getColor, put = setColor)) unsigned int Color;

        inline float getThickness() const {
            return thickness;
        }

        inline void setThickness(float radius) {
            this->thickness = thickness;
        }

        __declspec(property(get = getThickness, put = setThickness)) float Thickness;

    };
}