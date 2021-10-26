#pragma once

#include "DrawingEffect.h"
#include <ui/style/ColorAttr.h>
#include <ui/Shape.h>

namespace Ghurund::UI {
    class ShadowEffect:public DrawingEffect {
    private:
        Color color;
        Shape* shape = nullptr;
        float radius = 2.0f;

    public:
        ShadowEffect(const Color& color = Ghurund::UI::Color(0, 0, 0, 0.6f)):color(color) {}

        ~ShadowEffect() {
            delete shape;
        }

        inline const Color& getColor() const {
            return color;
        }

        virtual void setColor(const Color& color) {
            this->color = color;
        }

        __declspec(property(get = getColor, put = setColor)) const Color& Color;

        inline Shape* getShape() {
            return shape;
        }

        virtual void setShape(Shape* shape) {
            delete this->shape;
            this->shape = shape;
        }

        __declspec(property(get = getShape, put = setShape)) Shape* Shape;

        inline float getRadius() const {
            return radius;
        }

        virtual void setRadius(float radius) {
            this->radius = radius;
        }

        __declspec(property(get = getRadius, put = setRadius)) float Radius;
    };
}