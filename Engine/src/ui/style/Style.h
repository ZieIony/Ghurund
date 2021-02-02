#pragma once

#include "ui/control/Control.h"

namespace Ghurund::UI {

    template<class ControlType>
    class Style {
    public:
        virtual ~Style() = 0 {}

        void apply(ControlType& control) {
            control.OnThemeChanged.add([this, &control](Control& c) {
                onThemeChanged(control);
                return true;
            });
            control.OnStateChanged.add([this, &control](Control& c) {
                onStateChanged(control);
                return true;
            });
        }

        virtual void onThemeChanged(ControlType& control) const {}

        virtual void onStateChanged(ControlType& control) const {}
    };
}