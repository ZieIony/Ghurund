#pragma once

#include "Color.h"
#include "core/string/String.h"

namespace Ghurund::UI {
    class Paint {
    private:
        Color color = 0;
        float thickness = 1.0f;

    public:
        inline const Color& getColor() const {
            return color;
        }

        inline void setColor(const Color& color) {
            this->color = color;
        }

        __declspec(property(get = getColor, put = setColor)) const Color& Color;

        inline float getThickness() const {
            return thickness;
        }

        inline void setThickness(float thickness) {
            this->thickness = thickness;
        }

        __declspec(property(get = getThickness, put = setThickness)) float Thickness;

    };
}