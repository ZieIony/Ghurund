#pragma once

#include "Control.h"
#include "ui/style/ColorAttr.h"

namespace Ghurund::UI {
    class ColorView:public Control {
    private:
        ColorAttr* color = nullptr;

    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        ColorView(const ColorAttr& color = ColorRef(Theme::COLOR_CONTROL)) {
            Color = color;
            preferredSize.width = PreferredSize::Width::FILL;
            preferredSize.height = PreferredSize::Height::FILL;
        }

        ~ColorView() {
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

        virtual void onDraw(ICanvas& canvas);

        virtual void load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();
    };

    class ColorViewBackgroundStyle:public TypedStyle<ColorView> {

        virtual void apply(ColorView& control) const;
    };

    class ColorViewControlStyle:public TypedStyle<ColorView> {

        virtual void apply(ColorView& control) const;
    };

    class ColorViewAccentStyle:public TypedStyle<ColorView> {

        virtual void apply(ColorView& control) const;
    };
}