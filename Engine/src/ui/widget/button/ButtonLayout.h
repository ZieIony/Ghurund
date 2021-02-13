#pragma once

#include "ui/control/ClickableControl.h"
#include "ui/widget/Layout.h"
#include "ui/widget/StateIndicator.h"

namespace Ghurund::UI {
    class ButtonLayout:public WidgetLayout {
    protected:
        ClickableControl* clickableControl = nullptr;
        StateIndicator* stateIndicator = nullptr;

        EventHandler<Control> stateHandler = [this](Control& control) {
            if (clickableControl->Pressed) {
                stateIndicator->State = IndicatorState::PRESSED;
            } else if (clickableControl->Focused || clickableControl->Hovered) {
                stateIndicator->State = IndicatorState::FOCUSED;
            } else {
                stateIndicator->State = IndicatorState::NONE;
            }
            return true;
        };

    public:
        ButtonLayout() {}

        ButtonLayout(Control* layout) {
            Root = layout;
            clickableControl = (Ghurund::UI::ClickableControl*)layout->find("clickable");
            stateIndicator = (Ghurund::UI::StateIndicator*)layout->find("state");
            clickableControl->StateChanged.add(stateHandler);
        }

        ~ButtonLayout() {
            if (clickableControl)
                clickableControl->StateChanged.remove(stateHandler);
        }

        inline ClickableControl* getClickableControl() {
            return clickableControl;
        }

        __declspec(property(get = getClickableControl)) ClickableControl* ClickableControl;

        inline StateIndicator* getStateIndicator() {
            return stateIndicator;
        }

        __declspec(property(get = getStateIndicator)) StateIndicator* StateIndicator;
    };

}