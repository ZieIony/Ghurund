#pragma once

#include "ButtonBinding.h"
#include "ui/control/ClickableControl.h"
#include "ui/widget/Widget.h"
#include "ui/widget/StateIndicator.h"

namespace Ghurund::UI {
    class Button:public Widget<ButtonBinding> {
    private:
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
            if (Layout->Clickable) {
                Layout->Clickable->stateChanged += stateHandler;
                Layout->Clickable->clicked += [this](Control&, const MouseClickedEventArgs& args) {
                    return clicked(args);
                };
            }
        }

    public:
        Event<Button, MouseClickedEventArgs> clicked = *this;

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };
}