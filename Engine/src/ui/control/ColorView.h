#pragma once

#include "Control.h"
#include "core/ScopedPointer.h"

namespace Ghurund::UI {
    class ColorView:public Control {
    private:
        unsigned int color;
        Paint paint;

        static inline const auto& CONSTRUCTOR = NoArgsConstructor<ColorView>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type& TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ColorView))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::TYPE);

            return TYPE;
        }

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
            canvas.fillRect(0, 0, Size.width, Size.height, paint);
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();
        
        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}