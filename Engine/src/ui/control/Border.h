#pragma once

#include "ControlContainer.h"

namespace Ghurund {
    class Border : public Control {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(Border);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<Border>();
        
        unsigned int color = 0x1f000000;

    public:
        Border(unsigned int color = 0x1f000000):color(color) {}

        inline unsigned int getColor() const {
            return color;
        }

        inline void setColor(unsigned int color) {
            this->color = color;
        }

        __declspec(property(get = getColor, put = setColor)) unsigned int Color;

        virtual void draw(Canvas& canvas) override {
            paint.setColor(color);
            canvas.drawRect(position.x, position.y, size.x, size.y, paint);
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<Border>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(Control::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}