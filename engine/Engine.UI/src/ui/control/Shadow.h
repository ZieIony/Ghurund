#pragma once

#include "Control.h"
#include "ui/Shape.h"
#include "ui/style/ColorAttr.h"
//#include "ui/image/Bitmap.h"

namespace Ghurund::UI {
    class Shadow: public Control {
    private:
        ColorAttr* color = nullptr;
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

        inline const ColorAttr& getColor() const {
            return *color;
        }

        inline void setColor(const ColorAttr& color) {
            delete this->color;
            this->color = (ColorAttr*)color.clone();
        }

        __declspec(property(get = getColor, put = setColor)) const ColorAttr& Color;

        inline Ghurund::UI::Shape* getShape() {
            return shape;
        }

        inline void setShape(Ghurund::UI::Shape* shape) {
            delete this->shape;
            if (shape) {
                this->shape = (Ghurund::UI::Shape*)shape->clone();
            } else {
                this->shape = nullptr;
            }
        }

        __declspec(property(get = getShape, put = setShape)) Ghurund::UI::Shape* Shape;

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