#pragma once

#include "Control.h"
#include "ui/Shape.h"
#include "ui/style/ColorAttr.h"

namespace Ghurund::UI {
    class Border: public Control {
    private:
        ColorAttr* color = nullptr;
        float thickness = 1.0f;
        Ghurund::UI::Shape* shape = nullptr;

    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        Border(const ColorAttr& color = ColorRef(Theme::COLOR_SECONDARY_ONBACKGROUND)) {
            Color = color;
            preferredSize.width = PreferredSize::Width::FILL;
            preferredSize.height = PreferredSize::Height::FILL;
        }

        ~Border() {
            delete shape;
            delete color;
        }

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
            this->shape = shape;
        }

        __declspec(property(get = getShape, put = setShape)) Ghurund::UI::Shape* Shape;

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

        virtual void onDraw(Ghurund::UI::ICanvas& canvas) override;

        virtual void load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };

    class BorderOnBackgroundStyle:public TypedStyle<Border> {
    public:
        void onStateChanged(Border& control) const;
    };

    class BorderAccentStyle:public TypedStyle<Border> {
    public:
        void onStateChanged(Border& control) const;
    };
}