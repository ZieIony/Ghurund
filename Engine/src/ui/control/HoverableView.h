#pragma once

#include "ui/control/ControlContainer.h"

namespace Ghurund::UI {
    class HoverableView:public ControlContainer {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(HoverableView);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<HoverableView>();

        bool hovered = false;

    public:
        inline bool isHovered() const {
            return hovered;
        }

        __declspec(property(get = isHovered)) bool Hovered;

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override {
            bool result = false;
            bool in = event.Position.x >= 0 && event.Position.x < Size.width&&
                event.Position.y >= 0 && event.Position.y < Size.height;
            if (in && !hovered) {
                hovered = true;
                onStateChanged();
                result = true;
            } else if (!in && hovered) {
                hovered = false;
                onStateChanged();
                result = true;
            }

            return result || __super::dispatchMouseMotionEvent(event);
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<HoverableView>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}