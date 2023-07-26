#pragma once

#include "ui/style/Style.h"

namespace Ghurund::UI {
    class Control;

    class DrawableViewStyle:public Style {
    public:
        virtual void onStateChanged(Control& control) const override;
    };

    class DrawableViewOnBackgroundStyle:public Style {
    public:
        virtual void onStateChanged(Control& control) const override;
    };

    class DrawableViewOnAccentStyle:public Style {
    public:
        virtual void onStateChanged(Control& control) const override;
    };

    class DrawableViewAccentStyle:public Style {
    public:
        virtual void onStateChanged(Control& control) const override;
    };
}