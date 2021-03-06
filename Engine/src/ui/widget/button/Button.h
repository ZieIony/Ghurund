#pragma once

#include "ButtonBinding.h"
#include "ui/control/ClickableControl.h"
#include "ui/widget/ContainerWidget.h"
#include "ui/widget/StateIndicator.h"

namespace Ghurund::UI {
    class ButtonLayout:public ButtonBinding {
    private:
        EventHandler<Control> stateHandler = [this](Control& control) {
            if (Clickable->Pressed) {
                State->State = IndicatorState::PRESSED;
            } else if (Clickable->Focused || Clickable->Hovered) {
                State->State = IndicatorState::FOCUSED;
            } else {
                State->State = IndicatorState::NONE;
            }
            return true;
        };

    public:
        ButtonLayout(Control* control):ButtonBinding(control) {
            Clickable->StateChanged.add(stateHandler);
        }
    };

    class Button:public ContainerWidget<ButtonLayout> {
    private:
        Event<Button, MouseClickedEventArgs> clicked = Event<Button, MouseClickedEventArgs>(*this);

    protected:
        static const Ghurund::Type& GET_TYPE();

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