#pragma once

#include "ui/Style.h"
#include "Separator.h"

namespace Ghurund::UI {
    class Theme;

    class SeparatorStyle:public Ghurund::UI::Style<Separator> {
    public:
        SeparatorStyle(Theme& theme);

        ~SeparatorStyle() = 0 {}

        virtual void apply(Separator& separator) const override;

        virtual void onStateChanged(Separator& separator) const override;
    };

    class HorizontalSeparatorStyle:public SeparatorStyle {
    public:
        HorizontalSeparatorStyle(Theme& theme):SeparatorStyle(theme) {}

        virtual void apply(Separator& separator) const override;
    };

    class VerticalSeparatorStyle:public SeparatorStyle {
    public:
        VerticalSeparatorStyle(Theme& theme):SeparatorStyle(theme) {}

        virtual void apply(Separator& separator) const override;
    };
}