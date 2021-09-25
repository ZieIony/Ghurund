#pragma once

#include "ButtonBinding.h"
#include "ui/control/ClickableControl.h"
#include "ui/widget/Widget.h"
#include "ui/widget/StateIndicator.h"

namespace Ghurund::UI {
    class Button:public Widget<ButtonBinding> {
    private:
        Event<Button, MouseClickedEventArgs> clicked = *this;
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

    protected:
        static const Ghurund::Core::Type& GET_TYPE();

        virtual void onLayoutChanged() override {
            if (!Layout)
                return;
            Layout->Clickable->StateChanged.add(stateHandler);
            Layout->Clickable->Clicked.add([this](Control&, const MouseClickedEventArgs& args) {
                return clicked(args);
            });
        }

    public:
        inline Event<Button, MouseClickedEventArgs>& getClicked() {
            return clicked;
        }

        __declspec(property(get = getClicked)) Event<Button, MouseClickedEventArgs>& Clicked;

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };
}