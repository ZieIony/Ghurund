#pragma once

#include "Control.h"
#include "ui/Shape.h"

namespace Ghurund::UI {
    class Border: public Control {
    private:
        Paint paint;
        Ghurund::UI::Shape* shape = nullptr;

        static inline const auto& CONSTRUCTOR = NoArgsConstructor<Border>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type& TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Border))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

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

        inline const Color& getColor() const {
            return paint.Color;
        }

        inline void setColor(const Color& color) {
            paint.Color = color;
        }

        __declspec(property(get = getColor, put = setColor)) const Color& Color;

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

        virtual void onLayout(float x, float y, float width, float height) override {
            __super::onLayout(x, y, width, height);
            if (shape)
                shape->Bounds = D2D1::RectF(Thickness / 2, Thickness / 2, width - Thickness / 2, height - Thickness / 2);
        }

        virtual void onDraw(Canvas& canvas) override;

        virtual Status load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}