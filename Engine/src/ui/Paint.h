#pragma once

#include "core/string/String.h"

namespace Ghurund::UI {
    class Paint {
    private:
        uint32_t color = 0;
        float thickness = 1.0f;

    public:
        inline uint32_t getColor() const {
            return color;
        }

        inline void setColor(uint32_t color) {
            this->color = color;
        }

        __declspec(property(get = getColor, put = setColor)) uint32_t Color;

        inline float getThickness() const {
            return thickness;
        }

        inline void setThickness(float thickness) {
            this->thickness = thickness;
        }

        __declspec(property(get = getThickness, put = setThickness)) float Thickness;

    };
}