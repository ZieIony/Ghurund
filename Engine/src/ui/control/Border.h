#pragma once

#include "Control.h"
#include "ui/Shape.h"

namespace Ghurund::UI {
    class Border: public Control {
    private:
        unsigned int color = 0x1f000000;
        Paint paint;
        Ghurund::UI::Shape* shape = nullptr;

        static inline const auto& CONSTRUCTOR = NoArgsConstructor<Border>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type& TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Border))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::TYPE);

            return TYPE;
        }

    public:
        Border(unsigned int color = 0x1f000000) {
            preferredSize.width = PreferredSize::Width::FILL;
            preferredSize.height = PreferredSize::Height::FILL;
            Color = color;
        }

        ~Border() {
            delete shape;
        }

        inline uint32_t getColor() const {
            return paint.Color;
        }

        inline void setColor(uint32_t color) {
            paint.Color = color;
        }

        __declspec(property(get = getColor, put = setColor)) uint32_t Color;

        inline Shape* getShape() {
            return shape;
        }

        inline void setShape(Shape* shape) {
            delete this->shape;
            this->shape = shape;
        }

        __declspec(property(get = getShape, put = setShape)) Shape* Shape;

        inline float getThickness() const {
            return paint.Thickness;
        }

        inline void setThickness(float thickness) {
            paint.Thickness = thickness;
        }

        __declspec(property(get = getThickness, put = setThickness)) float Thickness;

        virtual void onDraw(Canvas& canvas) override {
            if (!Color || Thickness < 0.1f)
                return;
            if (shape) {
                canvas.drawShape(*shape, paint);
            } else {
                canvas.drawRect(Position.x + Thickness / 2, Position.y + Thickness / 2, Size.width - Thickness, Size.height - Thickness, paint);
            }
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}