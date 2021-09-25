#pragma once

#include "Control.h"
#include "ui/Color.h"

namespace Ghurund::UI {
    class ColorView:public Control {
    private:
        Color color;

    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        ColorView(const Color& color = 0x1f000000):color(color) {
            preferredSize.width = PreferredSize::Width::FILL;
            preferredSize.height = PreferredSize::Height::FILL;
        }

        inline const Color& getColor() {
            return color;
        }

        inline void setColor(const Color& color) {
            this->color = color;
        }

        __declspec(property(get = getColor, put = setColor)) const Color& Color;

        virtual void onDraw(Canvas& canvas);

        virtual Status load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };

    class ColorViewBackgroundStyle:public Style {

        virtual void onThemeChanged(Control& control) const;
    };

    class ColorViewControlStyle:public Style {

        virtual void onThemeChanged(Control& control) const;
    };

    class ColorViewAccentStyle:public Style {

        virtual void onThemeChanged(Control& control) const;
    };
}