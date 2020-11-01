#pragma once

#include "core/ScopedPointer.h"
#include "ui/control/ControlGroup.h"
#include "ui/layout/StackLayoutManager.h"

namespace Ghurund::UI {
    class StackLayout : public ControlGroup {
    private:
        StackLayoutManager layoutManager;

    public:
        inline Alignment& getAlignment() {
            return layoutManager.alignment;
        }

        inline void setAlignment(const Alignment& alignment) {
            layoutManager.alignment = alignment;
        }

        __declspec(property(get = getAlignment, put = setAlignment)) Alignment& Alignment;

        virtual void onMeasure(float parentWidth, float parentHeight) override {
            measuredSize = layoutManager.measure(*this, parentWidth, parentHeight);
        }

        virtual void onLayout(float x, float y, float width, float height) override {
            layoutManager.layout(*this, x, y, width, height);
        }

        static const Ghurund::Type& TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder<StackLayout>(NAMESPACE_NAME, GH_STRINGIFY(StackLayout))
                .withConstructor(NoArgsConstructor<StackLayout>())
                .withSupertype(__super::TYPE());

            return TYPE;
        }

        virtual const Ghurund::Type& getType() const override {
            return TYPE();
        }
    };

    typedef ScopedPointer<StackLayout> StackLayoutPtr;
}