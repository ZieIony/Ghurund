#pragma once

#include "Control.h"
#include "core/ScopedPointer.h"

namespace Ghurund::UI {
    class ColorView:public Control {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(ColorView);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<ColorView>();

        unsigned int color;
        Paint paint;

    public:
        ColorView(unsigned int color = 0x1b000000):color(color) {
            preferredSize.width = PreferredSize::Width::FILL;
            preferredSize.height = PreferredSize::Height::FILL;
        }

        inline unsigned int getColor() const {
            return color;
        }

        inline void setColor(unsigned int color) {
            this->color = color;
        }

        __declspec(property(get = getColor, put = setColor)) unsigned int Color;

        virtual void onDraw(Canvas& canvas) {
            if (!color)
                return;
            paint.Color = color;
            canvas.fillRect(0, 0, size.width, size.height, paint);
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<ColorView>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef ScopedPointer<ColorView> ColorViewPtr;
}