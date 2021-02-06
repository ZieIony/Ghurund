#pragma once

namespace Ghurund::UI {
    class Control;

    class Style {
    public:
        virtual ~Style() = 0 {}

        virtual void onThemeChanged(Control& control) const {}

        virtual void onStateChanged(Control& control) const {}
    };
}