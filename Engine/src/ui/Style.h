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

    template<class ControlType, class LayoutType>
    class StyleWithLayout:public Style<ControlType> {
    public:
        StyleWithLayout(Theme& theme):Style(theme) {}

        virtual LayoutType* makeLayout() const = 0;
    };
}