#pragma once

#include "ui/style/Style.h"
#include "Separator.h"

namespace Ghurund::UI {
    class Theme;

    class SeparatorStyle:public Ghurund::UI::Style {
    public:
        ~SeparatorStyle()// = 0 
        {}

        virtual void onThemeChanged(Control& separator) const override;

        virtual void onStateChanged(Control& separator) const override;
    };

    class SeparatorHorizontalStyle:public SeparatorStyle {
    public:
        virtual void onThemeChanged(Control& separator) const override;
    };

    class SeparatorVerticalStyle:public SeparatorStyle {
    public:
        virtual void onThemeChanged(Control& separator) const override;
    };
}