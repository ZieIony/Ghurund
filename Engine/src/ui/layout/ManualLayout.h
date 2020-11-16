#pragma once

#include "ManualLayoutManager.h"
#include "core/ScopedPointer.h"
#include "ui/control/ControlGroup.h"

namespace Ghurund::UI {
    class ManualLayout: public ControlGroup {
    private:
        ManualLayoutManager layoutManager;
        ListChildrenProvider childrenProvider = ListChildrenProvider(*this);

        static inline const auto& CONSTRUCTOR = NoArgsConstructor<ManualLayout>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ManualLayout))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::TYPE);

            return TYPE;
        }

    public:
        virtual void onMeasure(float parentWidth, float parentHeight) override {
            measuredSize = layoutManager.measure(*this, childrenProvider, parentWidth, parentHeight);
        }

        virtual void onLayout(float x, float y, float width, float height) override {
            layoutManager.layout(*this, childrenProvider, x, y, width, height);
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef ScopedPointer<ManualLayout> ManualLayoutPtr;
}