#pragma once

#include "core/math/Rect.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class Shape {
    protected:
        FloatRect bounds;

    public:
        Shape():bounds({}) {}

        Shape(const FloatRect& bounds):bounds(bounds) {}

        virtual ~Shape() = 0 {};

        inline const FloatRect& getBounds() const {
            return bounds;
        }

        virtual void setBounds(const FloatRect& bounds) {
            this->bounds = bounds;
        }

        __declspec(property(get = getBounds, put = setBounds)) const FloatRect& Bounds;
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::Shape>();
}
