#include "ghpch.h"
#include "TextTabLayout.h"

#include "ui/style/Theme.h"

namespace Ghurund::UI {
    TextTabLayout::TextTabLayout(Theme& theme):TabLayout(nullptr), theme(theme) {
        stack = ghnew StackLayout();
        /*textView->TextFormat = theme.TextFormats[Theme::TEXTFORMAT_BUTTON];
        paddingContainer->Child = textView;
        paddingContainer->Padding.All = 4;
        stack->PreferredSize.width = PreferredSize::Width::WRAP;
        stack->PreferredSize.height = PreferredSize::Height::WRAP;
        stack->Children = { backgroundView, border, paddingContainer };
        selectableView = ghnew Ghurund::UI::SelectableView();
        selectableView->Child = stack;
        Root = selectableView;*/
    }

    void TextTabLayout::onStateChanged(Control& control) {
        /*if (!control.Enabled) {
            TextBlock->TextColor = theme.Colors[Theme::COLOR_DISABLED_ONBACKGROUND];
            backgroundView->Color = 0;
            border->Color = 0;
        } else if (selectableView->Selected) {
            backgroundView->Color = theme.Colors[Theme::COLOR_ACCENT];
            border->Color = 0;
            TextBlock->TextColor = theme.Colors[Theme::COLOR_PRIMARY_ONACCENT];
        } else if (selectableView->Pressed) {
            TextBlock->TextColor = theme.Colors[Theme::COLOR_PRIMARY_ONBACKGROUND];
            backgroundView->Color = theme.Colors[Theme::COLOR_BACKGR0UND];
            //border->Color = theme.getColorAccentDark();
        } else if (selectableView->Hovered || control.Focused) {
            TextBlock->TextColor = theme.Colors[Theme::COLOR_PRIMARY_ONBACKGROUND];
            backgroundView->Color = theme.Colors[Theme::COLOR_BACKGR0UND];
            border->Color = theme.Colors[Theme::COLOR_ACCENT];
        } else {
            TextBlock->TextColor = theme.Colors[Theme::COLOR_PRIMARY_ONBACKGROUND];
            backgroundView->Color = theme.Colors[Theme::COLOR_BACKGR0UND];
            border->Color = 0;
        }*/
    }
}