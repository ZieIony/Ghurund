#pragma once

#include "core/reflection/Type.h"
#include "ui/Shape.h"

namespace Ghurund::UI::DirectX {
    using namespace Ghurund::Core;

    class Shape:public Ghurund::UI::Shape {};

    class Rect:public Shape {
    public:
        virtual Rect* clone() const override {
            auto rect = ghnew Rect();
            rect->Bounds = Bounds;
            return rect;
        }
    };

    class RoundRect:public Shape {
    private:
        float cornerRadius;

    public:
        RoundRect(float cornerRadius = 2.0f):cornerRadius(cornerRadius) {}

        inline float getCornerRadius() const {
            return cornerRadius;
        }

        inline void setCornerRadius(float radius) {
            this->cornerRadius = radius;
        }

        __declspec(property(get = getCornerRadius, put = setCornerRadius)) float CornerRadius;

        virtual RoundRect* clone() const override {
            auto rect = ghnew RoundRect();
            rect->Bounds = Bounds;
            rect->CornerRadius = CornerRadius;
            return rect;
        }
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::DirectX::Shape>();
}
