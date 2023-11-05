#pragma once

#include "Control.h"
#include "ui/Shape.h"
#include "ui/style/AttrProperty.h"
#include "ui/style/ColorAttr.h"

namespace Ghurund::UI {
    class Border: public Control {
    private:
        AttrProperty<ColorAttr, Color> color;
        float thickness = 1.0f;
        Ghurund::UI::Shape* shape = nullptr;

    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        virtual void onThemeChanged() override;

        virtual void onStateChanged() override;

        virtual void onLayout(float x, float y, float width, float height) override {
            __super::onLayout(x, y, width, height);
            if (shape)
                shape->Bounds = FloatRect{ thickness / 2, thickness / 2, width - thickness / 2, height - thickness / 2 };
        }

        virtual void onDraw(Ghurund::UI::ICanvas& canvas) override;

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Border::GET_TYPE();

        Border(const ColorAttr& color = ColorRef(Theme::COLOR_SECONDARY_ONBACKGROUND)) :color(color) {}

        ~Border() {
            delete shape;
        }

        inline void setColor(const ColorAttr& color) {
            this->color.set(color);
        }

        __declspec(property(put = setColor)) const ColorAttr& Color;

        inline void setShape(std::unique_ptr<Ghurund::UI::Shape> shape) {
            delete this->shape;
            this->shape = shape.release();
        }

        __declspec(property(put = setShape)) std::unique_ptr<Ghurund::UI::Shape> Shape;

        inline void setThickness(float thickness) {
            this->thickness = thickness;
        }

        __declspec(property(put = setThickness)) float Thickness;
    };
}