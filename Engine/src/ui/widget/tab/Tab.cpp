#include "TextTab.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    TextTabStyle::TextTabStyle(Theme& theme):StyleWithLayout<Tab, TabLayout>(theme) {}

    void TextTabStyle::onStateChanged(Tab& tab) const {
        TextTabLayout& layout = (TextTabLayout&)tab.Layout;
        if (!tab.Enabled) {
            layout.TextView->TextColor = theme.getColorForegroundDisabledOnBackground();
            layout.BackgroundView->Color = 0;
            layout.Border->Color = 0;
        } else if (layout.SelectableView->Selected) {
            layout.BackgroundView->Color = theme.getColorAccent();
            layout.Border->Color = 0;
            layout.TextView->TextColor = theme.getColorForegroundPrimaryOnAccent();
        } else if (layout.SelectableView->Pressed) {
            layout.TextView->TextColor = theme.getColorForegroundPrimaryOnBackground();
            layout.BackgroundView->Color = theme.getColorBackground();
            layout.Border->Color = theme.getColorAccentDark();
        } else if (layout.SelectableView->Hovered) {
            layout.TextView->TextColor = theme.getColorForegroundPrimaryOnBackground();
            layout.BackgroundView->Color = theme.getColorBackground();
            layout.Border->Color = theme.getColorAccent();
        } else {
            layout.TextView->TextColor = theme.getColorForegroundPrimaryOnBackground();
            layout.BackgroundView->Color = theme.getColorBackground();
            layout.Border->Color = 0;
        }
        layout.TextView->invalidateCache();
    }

    TextTabLayout* TextTabStyle::makeLayout() const {
        return ghnew TextTabLayout();
    }

    void TextTabStyle::apply(Tab& tab) const {
        __super::apply(tab);
        TextTabLayout& layout = (TextTabLayout&)tab.Layout;
        layout.TextView->Font = theme.getButtonFont();
        layout.PaddingContainer->Padding.All = 4;
    }

    Tab::Tab(Ghurund::UI::StyleWithLayout<Tab, Ghurund::UI::TabLayout>* style):Widget<Tab, TabLayout>(style) {}

}