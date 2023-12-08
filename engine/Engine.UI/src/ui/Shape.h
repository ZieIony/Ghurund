#pragma once

#include "core/math/Rect.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class Shape:public Object {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Shape::GET_TYPE();
#pragma endregion

    protected:
        FloatRect bounds;

    public:
        Shape():bounds({}) {}

        Shape(const FloatRect& bounds):bounds(bounds) {}

        virtual ~Shape()
        //    = 0   // TODO: a destructor cannot be abstract
        {};

        inline const FloatRect& getBounds() const {
            return bounds;
        }

        virtual void setBounds(const FloatRect& bounds) {
            this->bounds = bounds;
        }

        __declspec(property(get = getBounds, put = setBounds)) const FloatRect& Bounds;
    };
}
