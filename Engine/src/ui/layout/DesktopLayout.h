#pragma once

#include "ManualLayoutManager.h"

#include "ui/Alignment.h"
#include "ui/control/ControlGroup.h"

namespace Ghurund::UI {
    class DesktopLayout:public ControlGroup {
    private:
        ManualLayoutManager layoutManager;
        ListChildrenProvider childrenProvider = ListChildrenProvider(*this);

        static inline const auto& CONSTRUCTOR = NoArgsConstructor<DesktopLayout>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(DesktopLayout))
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
}