#pragma once

#include "ui/Style.h"
#include "ToolbarLayout.h"

namespace Ghurund::UI {
    class Theme;
    class Toolbar;

    class ToolbarStyle:public Ghurund::UI::StyleWithLayout<Toolbar, ToolbarLayout> {
    protected:
        Theme& theme;

    public:
        ToolbarStyle(Theme& theme);

        virtual void apply(Toolbar& toolbar) const override;

        virtual ToolbarLayout* makeLayout() const override;
    };

    class ToolbarWithBackgroundStyle:public ToolbarStyle {
    public:
        ToolbarWithBackgroundStyle(Theme& theme);

        virtual void apply(Toolbar& toolbar) const override;

        virtual void onStateChanged(Toolbar& toolbar) const override;

        virtual class ToolbarWithBackgroundLayout* makeLayout() const override;
    };

}