#pragma once

#include "ui/control/ClickableControl.h"
#include "ui/widget/ContentWidget.h"
#include "ui/widget/StateIndicator.h"

namespace Ghurund::UI {
    class Button:public ContentWidget {
    private:
        Ghurund::UI::ClickableControl* clickable = nullptr;
        Ghurund::UI::StateIndicator* state = nullptr;

        EventHandler<Control> stateHandler = [this](Control& control) {
            if (clickable->Pressed) {
                state->State = IndicatorState::PRESSED;
            } else if (clickable->Focused || clickable->Hovered) {
                state->State = IndicatorState::FOCUSED;
            } else {
                state->State = IndicatorState::NONE;
            }
            return true;
        };

    protected:
        virtual void bind() override {
            __super::bind();
            clickable = (Ghurund::UI::ClickableControl*)find("clickable");
            state = (Ghurund::UI::StateIndicator*)find("state");
            /*clickable->stateChanged += stateHandler;
            clickable->clicked += [this](Control&, const MouseClickedEventArgs& args) {
                return clicked(args);
            };*/
        }

    public:
        Event<Button, MouseClickedEventArgs> clicked = *this;

        static const Ghurund::Core::Type& GET_TYPE();

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };
}