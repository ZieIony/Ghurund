#pragma once

#include "Control.h"
#include "ui/Shape.h"

struct ID2D1SolidColorBrush;

namespace Ghurund::UI {
    class BitmapImage;

    class Shadow: public Control {
    private:
        unsigned int color;
        Ghurund::UI::Shape* shape = nullptr;
        float radius = 2.0f;
        BitmapImage* image;
        ID2D1SolidColorBrush* fillBrush = nullptr;

    protected:
        static const Ghurund::Type& GET_TYPE();

    public:
        Shadow(unsigned int color = 0xaf000000);

        ~Shadow();

        inline uint32_t getColor() const {
            return color;
        }

        inline void setColor(uint32_t color) {
            this->color = color;
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

        inline float getRadius() const {
            return radius;
        }

        inline void setRadius(float radius) {
            this->radius = radius;
        }

        __declspec(property(get = getRadius, put = setRadius)) float Radius;

        virtual void onLayout(float x, float y, float width, float height) override;

        virtual void onDraw(Canvas& canvas) override;

        virtual Status load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    class ShadowButtonStyle:public Style {
    public:
        virtual void onStateChanged(Control& control) const override {
            if (control.Enabled) {
                ((Shadow&)control).Radius = 2;
            } else {
                ((Shadow&)control).Radius = 0;
            }
        }
    };
}