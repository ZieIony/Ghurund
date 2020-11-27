#pragma once

#include "ControlContainer.h"
#include "ui/Shape.h"

namespace Ghurund::UI {
    class Clip:public ControlContainer {
    private:
        Shape* shape = nullptr;

        static inline const auto& CONSTRUCTOR = NoArgsConstructor<Clip>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type& TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Clip))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::TYPE);

            return TYPE;
        }

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

        __declspec(property(get = getShape, put = setShape)) Shape* Shape;

        virtual void onLayout(float x, float y, float width, float height) override {
            if (shape)
                shape->Bounds = D2D1::RectF(x, y, x + width, y + height);
            __super::onLayout(x, y, width, height);
        }

        virtual void onDraw(Canvas& canvas) override {
            if (shape) {
                canvas.clipShape(*shape);
                __super::onDraw(canvas);
                canvas.restoreClipShape();
            } else {
                canvas.clipRect(0, 0, Size.width, Size.height);
                __super::onDraw(canvas);
                canvas.restoreClipRect();
            }
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}