#pragma once

#include "Control.h"
#include "ui/Shape.h"
#include "ui/style/AttrProperty.h"
#include "ui/style/ColorAttr.h"
//#include "ui/image/Bitmap.h"

namespace Ghurund::UI {
    class Shadow: public Control {
    private:
        AttrProperty<ColorAttr, Color> color;
        Ghurund::UI::Shape* shape = nullptr;
        float radius = 2.0f;
        //Bitmap* bitmap = nullptr;
        //ID2D1SolidColorBrush* fillBrush = nullptr;

    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Shadow::GET_TYPE();

        Shadow(const ColorAttr& color = ColorValue(Ghurund::UI::Color(0, 0, 0, 0.6f)));

        ~Shadow();

        inline void setColor(const ColorAttr& color) {
            this->color.set(color);
        }

        __declspec(property(put = setColor)) const ColorAttr& Color;

        inline void setShape(std::unique_ptr<Ghurund::UI::Shape> shape) {
            delete this->shape;
            this->shape = shape.release();
        }

        __declspec(property(put = setShape)) std::unique_ptr<Ghurund::UI::Shape> Shape;

        inline float getRadius() const {
            return radius;
        }

        inline void setRadius(float radius) {
            this->radius = radius;
        }

        __declspec(property(get = getRadius, put = setRadius)) float Radius;

        virtual void onLayout(float x, float y, float width, float height) override;

        virtual void onDraw(Ghurund::UI::ICanvas& canvas) override;
    };

    class ShadowButtonStyle:public TypedStyle<Shadow> {
    public:
        virtual void onStateChanged(Shadow& control) const override {
            control.Radius = control.Enabled ? 2.0f : 0.0f;
        }
    };
}