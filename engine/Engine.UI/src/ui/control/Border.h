#pragma once

#include "Control.h"
#include "ui/Color.h"
#include "ui/Shape.h"

namespace Ghurund::UI {
    class Border: public Control {
    private:
        Color color;
        float thickness = 1.0f;
        Ghurund::UI::Shape* shape = nullptr;

    protected:
        static const Ghurund::Type& GET_TYPE();

    public:
        Border(const Color& color = 0x1f000000):color(color) {
            preferredSize.width = PreferredSize::Width::FILL;
            preferredSize.height = PreferredSize::Height::FILL;
        }

        ~Border() {
            delete shape;
        }

        inline const Color& getColor() const {
            return color;
        }

        inline void setColor(const Color& color) {
            this->color = color;
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
            return thickness;
        }

        inline void setThickness(float thickness) {
            this->thickness = thickness;
        }

        __declspec(property(get = getThickness, put = setThickness)) float Thickness;

        virtual void onLayout(float x, float y, float width, float height) override {
            __super::onLayout(x, y, width, height);
            if (shape)
                shape->Bounds = FloatRect{ Thickness / 2, Thickness / 2, width - Thickness / 2, height - Thickness / 2 };
        }

        virtual void onDraw(Canvas& canvas) override;

        virtual Status load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    class BorderOnBackgroundStyle:public Style {
    public:
        void onStateChanged(Control& control) const;
    };

    class BorderAccentStyle:public Style {
    public:
        void onStateChanged(Control& control) const;
    };
}