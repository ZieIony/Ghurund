#include "TextTabLayout.h"
#include "ui/Theme.h"

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
        root = selectableView;
    }

    void TextTabLayout::onStateChanged(Control& control) {
        if (!control.Enabled) {
            TextBlock->TextColor = theme.getColorForegroundDisabledOnBackground();
            backgroundView->Color = 0;
            border->Color = 0;
        } else if (selectableView->Selected) {
            backgroundView->Color = theme.getColorAccent();
            border->Color = 0;
            TextBlock->TextColor = theme.getColorForegroundPrimaryOnAccent();
        } else if (selectableView->Pressed) {
            TextBlock->TextColor = theme.getColorForegroundPrimaryOnBackground();
            backgroundView->Color = theme.getColorBackground();
            border->Color = theme.getColorAccentDark();
        } else if (selectableView->Hovered || control.Focused) {
            TextBlock->TextColor = theme.getColorForegroundPrimaryOnBackground();
            backgroundView->Color = theme.getColorBackground();
            border->Color = theme.getColorAccent();
        } else {
            TextBlock->TextColor = theme.getColorForegroundPrimaryOnBackground();
            backgroundView->Color = theme.getColorBackground();
            border->Color = 0;
        }
    }
}