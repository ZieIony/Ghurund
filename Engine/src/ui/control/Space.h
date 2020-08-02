#pragma once

#include "Control.h"

namespace Ghurund {
    class Space :public Control {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(Space);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<Space>();

    public:
        virtual void draw(Canvas& canvas) {}

        inline static const Ghurund::Type& TYPE = TypeBuilder<Space>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(Control::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}