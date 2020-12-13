#pragma once

#include "ui/Style.h"
#include "Separator.h"

namespace Ghurund::UI {
    class Theme;

    class SeparatorStyle:public Ghurund::UI::Style2<Separator> {
    public:
        ~SeparatorStyle() = 0 {}

        virtual void onThemeChanged(Separator& separator) const override;

        virtual void onStateChanged(Separator& separator) const override;
    };

    class HorizontalSeparatorStyle:public SeparatorStyle {
    public:
        virtual void onThemeChanged(Separator& separator) const override;
    };

    class VerticalSeparatorStyle:public SeparatorStyle {
    public:
        virtual void onThemeChanged(Separator& separator) const override;
    };
}