#pragma once

#include "Control.h"
#include "core/SharedPointer.h"

namespace Ghurund::UI {
    class ColorView:public Control {
    private:
        Paint paint;

    protected:
        static const Ghurund::Type& GET_TYPE() {
            static const auto CONSTRUCTOR = NoArgsConstructor<ColorView>();
            static const Ghurund::Type& TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ColorView))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

    public:
        ColorView() {
            preferredSize.width = PreferredSize::Width::FILL;
            preferredSize.height = PreferredSize::Height::FILL;
        }

        ColorView(const Color& color):ColorView() {
            Color = color;
        }

        inline const Color& getColor() {
            return paint.Color;
        }

        inline void setColor(const Color& color) {
            paint.Color = color;
        }

        __declspec(property(get = getColor, put = setColor)) const Color& Color;

        virtual void onDraw(Canvas& canvas) {
            if (!paint.Color)
                return;
            canvas.fillRect(0, 0, Size.width, Size.height, paint);
        }

        virtual Status load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
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