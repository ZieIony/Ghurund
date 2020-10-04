#pragma once

#include "ui/Style.h"
#include "MenuBarLayout.h"

namespace Ghurund::UI {
    class Theme;
    class MenuBar;

    class MenuBarStyle:public Ghurund::UI::StyleWithLayout<MenuBar, MenuBarLayout> {
    protected:
        Theme& theme;

    public:
        MenuBarStyle(Theme& theme);

        virtual void apply(MenuBar& menuBar) const override;

        virtual MenuBarLayout* makeLayout() const override;
    };

    class MenuBarWithBackgroundStyle:public MenuBarStyle {
    public:
        MenuBarWithBackgroundStyle(Theme& theme);

        virtual void apply(MenuBar& menuBar) const override;

        virtual void onStateChanged(MenuBar& menuBar) const override;

        virtual class MenuBarWithBackgroundLayout* makeLayout() const override;
    };

}