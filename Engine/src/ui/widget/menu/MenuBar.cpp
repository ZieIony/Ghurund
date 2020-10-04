#include "MenuBar.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    MenuBar::MenuBar(StyleWithLayout<MenuBar, MenuBarLayout>* style):Widget<MenuBar, MenuBarLayout>(style) {
        Layout.AdapterView->Items = ghnew ListItemSource<MenuItem*>(items);
    }

    MenuBarStyle::MenuBarStyle(Theme& theme) : Ghurund::UI::StyleWithLayout<MenuBar, class MenuBarLayout>(theme), theme(theme) {}

    void MenuBarStyle::apply(MenuBar& menuBar) const {
        menuBar.PreferredSize.height = PreferredSize::Height::WRAP;
        MenuBarLayout& layout = (MenuBarLayout&)menuBar.Layout;
        layout.AdapterView->PreferredSize.height = PreferredSize::Height::WRAP;
        layout.AdapterView->LayoutManager = ghnew HorizontalLayoutManager<MenuItem*, Control>();
        layout.AdapterView->Adapters.add(ghnew ButtonMenuBarAdapter(theme));
    }

    class MenuBarLayout* MenuBarStyle::makeLayout() const {
        return ghnew class MenuBarLayout();
    }

    MenuBarWithBackgroundStyle::MenuBarWithBackgroundStyle(Theme& theme):MenuBarStyle(theme) {}

    void MenuBarWithBackgroundStyle::apply(MenuBar& menuBar) const {
        menuBar.PreferredSize.height = PreferredSize::Height::WRAP;
        MenuBarWithBackgroundLayout& layout = (MenuBarWithBackgroundLayout&)menuBar.Layout;
        layout.BackgroundView->Color = theme.getColorBackground();
        layout.AdapterView->PreferredSize.height = PreferredSize::Height::WRAP;
        layout.AdapterView->LayoutManager = ghnew HorizontalLayoutManager<MenuItem*, Control>();
        layout.AdapterView->Adapters.add(ghnew ButtonMenuBarAdapter(theme));
    }

    void MenuBarWithBackgroundStyle::onStateChanged(MenuBar& menuBar) const {
        MenuBarWithBackgroundLayout& layout = ((MenuBarWithBackgroundLayout&)menuBar.Layout);
        layout.BackgroundView->Color = theme.getColorBackground();
    }

    MenuBarWithBackgroundLayout* MenuBarWithBackgroundStyle::makeLayout() const {
        return ghnew MenuBarWithBackgroundLayout();
    }
}
