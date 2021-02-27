#pragma once

#include "ButtonBinding.h"
#include "ui/control/ClickableControl.h"
#include "ui/widget/ContainerWidget.h"
#include "ui/widget/StateIndicator.h"

namespace Ghurund::UI {
    class Button:public ContainerWidget<ButtonBinding> {
    protected:
        static const Ghurund::Type& GET_TYPE();

        EventHandler<Control> stateHandler = [this](Control& control) {
            if (Layout->Clickable->Pressed) {
                Layout->State->State = IndicatorState::PRESSED;
            } else if (Layout->Clickable->Focused || Layout->Clickable->Hovered) {
                Layout->State->State = IndicatorState::FOCUSED;
            } else {
                Layout->State->State = IndicatorState::NONE;
            }
            return true;
        };

        virtual void onLayoutChanged() override {
            __super::onLayoutChanged();
            if (Layout)
                Layout->Clickable->StateChanged.add(stateHandler);
        }

    public:
        inline bool isHovered() const {
            return Layout->Clickable->Hovered;
        }

        __declspec(property(get = isHovered)) bool Hovered;

        inline const MousePressed& isPressed() const {
            return Layout->Clickable->Pressed;
        }

        __declspec(property(get = isPressed)) MousePressed& Pressed;

        inline Event<Control, MouseClickedEventArgs>& getClicked() {
            return Layout->Clickable->Clicked;
        }

        __declspec(property(get = getClicked)) Event<Control, MouseClickedEventArgs>& Clicked;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}