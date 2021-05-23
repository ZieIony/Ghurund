#pragma once

#include "ControlContainer.h"
#include "ui/Shape.h"

#include "reflection_41ff1f3a_5073_416e_9f76_74d0e31bdf85.h"

namespace Ghurund::UI {
    class Clip:public ControlContainer {
        reflection_41ff1f3a_5073_416e_9f76_74d0e31bdf85

    private:
        Shape* shape = nullptr;

    public:
        ~Clip() {
            delete shape;
        }

        inline Shape* getShape() {
            return shape;
        }

        inline void setShape(Shape* shape) {
            this->shape = shape;
        }

        __declspec(property(get = getShape, put = setShape)) Ghurund::UI::Shape* Shape;

        virtual void onLayout(float x, float y, float width, float height) override {
            __super::onLayout(x, y, width, height);
            if (shape)
                shape->Bounds = FloatRect{ 0, 0, width, height };
        }

        virtual void onDraw(Canvas& canvas) override;

        virtual Status load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;
    };
}