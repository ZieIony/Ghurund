#pragma once

#include "core/Pointer.h"

namespace Ghurund::UI {
    class Theme;
    class Control;

    class BaseStyle:public Pointer {
    protected:
        Theme& theme;

    public:
        BaseStyle(Theme& theme):theme(theme) {}

        virtual void apply(Control& control) const {}

        virtual void onStateChanged(Control& control) const {}
    };

    template<class ControlType>
    class Style:public BaseStyle {
    public:
        Style(Theme& theme):BaseStyle(theme) {}

        virtual void apply(Control& control) const {
            apply((ControlType&)control);
        }

        virtual void apply(ControlType& control) const {}

        virtual void onStateChanged(Control& control) const {
            onStateChanged((ControlType&)control);
        }

        virtual void onStateChanged(ControlType& control) const {}
    };

    template<class ControlType>
    class Style2 {
    public:
        virtual ~Style2() = 0 {}

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