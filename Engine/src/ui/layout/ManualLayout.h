#pragma once

#include "ManualLayoutManager.h"
#include "core/ScopedPointer.h"
#include "ui/control/ControlGroup.h"

namespace Ghurund::UI {
    class ManualLayout: public ControlGroup {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(ManualLayout);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<ManualLayout>();

        ManualLayoutManager layoutManager;

    public:
        virtual void onMeasure(float parentWidth, float parentHeight) override {
            measuredSize = layoutManager.measure(*this, parentWidth, parentHeight);
        }

        virtual void onLayout(float x, float y, float width, float height) override {
            layoutManager.layout(*this, x, y, width, height);
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<ManualLayout>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::TYPE());

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef ScopedPointer<ManualLayout> ManualLayoutPtr;
}