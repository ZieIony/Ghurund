#include "TextTab.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    TextTabStyle::TextTabStyle(Theme& theme):StyleWithLayout<Tab, TabLayout>(theme) {}

    void TextTabStyle::onStateChanged(Tab& tab) const {
        TextTabLayout& layout = (TextTabLayout&)tab.Layout;
        if (!tab.Enabled) {
            layout.TextBlock->TextColor = theme.getColorForegroundDisabledOnBackground();
            layout.BackgroundView->Color = 0;
            layout.Border->Color = 0;
        } else if (layout.SelectableView->Selected) {
            layout.BackgroundView->Color = theme.getColorAccent();
            layout.Border->Color = 0;
            layout.TextBlock->TextColor = theme.getColorForegroundPrimaryOnAccent();
        } else if (layout.SelectableView->Pressed) {
            layout.TextBlock->TextColor = theme.getColorForegroundPrimaryOnBackground();
            layout.BackgroundView->Color = theme.getColorBackground();
            layout.Border->Color = theme.getColorAccentDark();
        } else if (layout.SelectableView->Hovered || tab.Focused) {
            layout.TextBlock->TextColor = theme.getColorForegroundPrimaryOnBackground();
            layout.BackgroundView->Color = theme.getColorBackground();
            layout.Border->Color = theme.getColorAccent();
        } else {
            layout.TextBlock->TextColor = theme.getColorForegroundPrimaryOnBackground();
            layout.BackgroundView->Color = theme.getColorBackground();
            layout.Border->Color = 0;
        }
        layout.TextBlock->invalidateCache();
    }

    TextTabLayout* TextTabStyle::makeLayout() const {
        return ghnew TextTabLayout();
    }

    void TextTabStyle::apply(Tab& tab) const {
        __super::apply(tab);
        TextTabLayout& layout = (TextTabLayout&)tab.Layout;
        layout.TextBlock->Font = theme.getButtonFont();
        layout.PaddingContainer->Padding.All = 4;
    }

    Tab::Tab(Ghurund::UI::StyleWithLayout<Tab, Ghurund::UI::TabLayout>* style):Widget<Tab, TabLayout>(style) {
        Focusable = true;
    }

}