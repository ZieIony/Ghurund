#pragma once

#include "ControlContainer.h"
#include "ui/layout/LayoutInflater.h"

namespace Ghurund::UI {
    class Padding : public ControlContainer {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(Padding);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<Padding>();

    public:
        float left, right, top, bottom;

        virtual void measure();

        void layout(float x, float y, float width, float height) {
            Control::layout(x, y, width, height);
            if (Child)
                Child->layout(left, top, width - left - right, height - top - bottom);
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<Padding>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        static Padding* inflate(LayoutInflater& inflater, json& json);
    };
}