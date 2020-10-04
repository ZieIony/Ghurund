#pragma once

#include "ControlGroup.h"
#include "core/ScopedPointer.h"
#include "ui/layout/StackLayoutManager.h"

namespace Ghurund::UI {
    class StackLayout : public ControlGroup {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(StackLayout);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<StackLayout>();
        
        StackLayoutManager layoutManager;

    public:
        inline Gravity& getGravity() {
            return layoutManager.gravity;
        }

        inline void setGravity(const Gravity& gravity) {
            layoutManager.gravity = gravity;
        }

        __declspec(property(get = getGravity, put = setGravity)) Gravity& Gravity;

        virtual void onMeasure(float parentWidth, float parentHeight) override {
            measuredSize = layoutManager.measure(*this, parentWidth, parentHeight);
        }

        virtual void onLayout(float x, float y, float width, float height) override {
            layoutManager.layout(*this, x, y, width, height);
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<StackLayout>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef ScopedPointer<StackLayout> StackLayoutPtr;
}