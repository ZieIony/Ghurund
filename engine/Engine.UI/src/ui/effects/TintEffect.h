#pragma once

#include "DrawingEffect.h"
#include "ui/Color.h"

namespace Ghurund::UI {
    class TintEffect:public DrawingEffect {
    private:
        Color color;

    public:
        TintEffect(const Color& color = Ghurund::UI::Color(0.0f, 0.0f, 0.0f, 0.0f)):color(color) {}

        inline const Color& getColor() const {
            return color;
        }

        virtual void setColor(const Color& color) {
            this->color = color;
        }

        __declspec(property(get = getColor, put = setColor)) const Color& Color;
    };
}