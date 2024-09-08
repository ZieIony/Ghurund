#pragma once

#include "DrawingEffect.h"
#include "core/Color.h"

namespace Ghurund::UI {
    class TintEffect:public DrawingEffect {
    private:
        Color color;

    public:
        TintEffect(const Color& color = 0):color(color) {}

        inline const Color& getColor() const {
            return color;
        }

        virtual void setColor(const Color& color) {
            this->color = color;
        }

        __declspec(property(get = getColor, put = setColor)) const Color& Color;
    };
}