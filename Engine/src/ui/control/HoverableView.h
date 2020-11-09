#pragma once

#include "ui/control/ControlContainer.h"

namespace Ghurund::UI {
    class HoverableView:public ControlContainer {
    private:
        bool hovered = false;

        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(HoverableView))
                .withConstructor(NoArgsConstructor<HoverableView>())
                .withSupertype(__super::TYPE);

            return TYPE;
        }

    protected:
        virtual bool onMouseMotionEvent(const MouseMotionEventArgs& event) override;

    public:
        inline bool isHovered() const {
            return hovered;
        }

        __declspec(property(get = isHovered)) bool Hovered;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}