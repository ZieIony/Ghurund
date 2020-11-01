#pragma once

#include "ControlContainer.h"
#include "ui/Padding.h"

namespace Ghurund::UI {
    class PaddingContainer: public ControlContainer {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(PaddingContainer);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<PaddingContainer>();

        Padding padding;
#ifdef _DEBUG
        Paint paint;
#endif

    public:
        PaddingContainer() {}

        PaddingContainer(float all) {
            padding.All = all;
        }

        PaddingContainer(float left, float top, float right, float bottom) {
            padding.left = left;
            padding.top = top;
            padding.right = right;
            padding.bottom = bottom;
        }

        inline Padding& getPadding() {
            return padding;
        }

        __declspec(property(get = getPadding)) Padding& Padding;

        virtual void onMeasure(float parentWidth, float parentHeight) override;

        virtual void onLayout(float x, float y, float width, float height) override;

        inline static const Ghurund::Type& TYPE = TypeBuilder<PaddingContainer>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef ScopedPointer<PaddingContainer> PaddingContainerPtr;
}