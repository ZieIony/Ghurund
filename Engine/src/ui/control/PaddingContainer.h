#pragma once

#include "ControlContainer.h"
#include "ui/Padding.h"

namespace Ghurund::UI {
    class PaddingContainer: public ControlContainer {
    private:
        Padding padding;

        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(PaddingContainer))
                .withConstructor(NoArgsConstructor<PaddingContainer>())
                .withSupertype(__super::TYPE);

            return TYPE;
        }

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

        inline void setPadding(const Padding& padding) {
            this->padding = padding;
        }

        __declspec(property(get = getPadding, put = setPadding)) Padding& Padding;

        virtual void onMeasure(float parentWidth, float parentHeight) override;

        virtual void onLayout(float x, float y, float width, float height) override;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef ScopedPointer<PaddingContainer> PaddingContainerPtr;

    inline PaddingContainerPtr makePaddingContainer(Control* child, const PreferredSize& preferredSize, const Padding& padding) {
        auto container = ghnew PaddingContainer();
        container->Child = child;
        container->PreferredSize = preferredSize;
        container->Padding = padding;
        return container;
    }
}