#include "TextTabLayout.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {
    void TextTabLayout::init() {
        stack = ghnew StackLayout();
        textView->TextStyle = theme.TextStyles[Theme::TEXTSTYLE_BUTTON];
        paddingContainer->Child = textView;
        paddingContainer->Padding.All = 4;
        stack->PreferredSize.width = PreferredSize::Width::WRAP;
        stack->PreferredSize.height = PreferredSize::Height::WRAP;
        stack->Children = { backgroundView, border, paddingContainer };
        selectableView = ghnew Ghurund::UI::SelectableView();
        selectableView->Child = stack;
        Root = selectableView;
    }

    void TextTabLayout::onStateChanged(Control& control) {
        if (!control.Enabled) {
            TextBlock->TextColor = theme.getColorForegroundDisabledOnBackground();
            backgroundView->Color = 0;
            border->Color = 0;
        } else if (selectableView->Selected) {
            backgroundView->Color = theme.Colors[Theme::COLOR_ACCENT];
            border->Color = 0;
            TextBlock->TextColor = theme.getColorForegroundPrimaryOnAccent();
        } else if (selectableView->Pressed) {
            TextBlock->TextColor = theme.getColorForegroundPrimaryOnBackground();
            backgroundView->Color = theme.Colors[Theme::COLOR_BACKGR0UND];
            //border->Color = theme.getColorAccentDark();
        } else if (selectableView->Hovered || control.Focused) {
            TextBlock->TextColor = theme.getColorForegroundPrimaryOnBackground();
            backgroundView->Color = theme.Colors[Theme::COLOR_BACKGR0UND];
            border->Color = theme.Colors[Theme::COLOR_ACCENT];
        } else {
            TextBlock->TextColor = theme.getColorForegroundPrimaryOnBackground();
            backgroundView->Color = theme.Colors[Theme::COLOR_BACKGR0UND];
            border->Color = 0;
        }
    }
}