#pragma once

#include "ControlContainer.h"
#include "ui/layout/LayoutInflater.h"
#include "ui/Padding.h"

namespace Ghurund::UI {
    class PaddingContainer : public ControlContainer {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(PaddingContainer);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<PaddingContainer>();

        Padding padding;
    public:
        inline Padding& getPadding() {
            return padding;
        }

        __declspec(property(get = getPadding)) Padding& Padding;

        virtual void measure();

        void layout(float x, float y, float width, float height) {
            Control::layout(x, y, width, height);
            if (Child)
                Child->layout(padding.left, padding.top, width - padding.left - padding.right, height - padding.top - padding.bottom);
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<PaddingContainer>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        static PaddingContainer* inflate(LayoutInflater& inflater, json& json);
    };
}