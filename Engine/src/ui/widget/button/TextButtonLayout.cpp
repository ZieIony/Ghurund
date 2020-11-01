#include "TextButton.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    void TextButtonLayout::onStateChanged(Control& control) {
        if (!control.Enabled) {
            textView->TextColor = theme.getColorForegroundDisabledOnBackground();
            border->Color = theme.getColorForegroundDisabledOnBackground();
            backgroundView->Color = theme.getColorControlDisabled();
        } else if (ClickableView->Pressed) {
            textView->TextColor = theme.getColorForegroundPrimaryOnBackground();
            border->Color = theme.getColorAccentDark();
            backgroundView->Color = theme.getColorControlActivated();
        } else if (ClickableView->Hovered || control.Focused) {
            textView->TextColor = theme.getColorForegroundPrimaryOnBackground();
            border->Color = theme.getColorAccent();
            backgroundView->Color = theme.getColorControlNormal();
        } else {
            textView->TextColor = theme.getColorForegroundPrimaryOnBackground();
            border->Color = theme.getColorForegroundPrimaryOnBackground();
            backgroundView->Color = theme.getColorControlNormal();
        }
    }

    void TextButtonFlatLayout::onStateChanged(Control& control) {
        if (!control.Enabled) {
            textView->TextColor = theme.getColorForegroundDisabledOnBackground();
            border->Color = 0;
        } else if (ClickableView->Pressed) {
            textView->TextColor = theme.getColorForegroundPrimaryOnBackground();
            border->Color = theme.getColorAccentDark();
        } else if (ClickableView->Hovered || control.Focused) {
            textView->TextColor = theme.getColorForegroundPrimaryOnBackground();
            border->Color = theme.getColorAccent();
        } else {
            textView->TextColor = theme.getColorForegroundPrimaryOnBackground();
            border->Color = 0;
        }
        backgroundView->Color = 0;
    }

    void TextButtonAccentLayout::onStateChanged(Control& control) {
        if (!control.Enabled) {
            textView->TextColor = theme.getColorForegroundDisabledOnBackground();
            backgroundView->Color = 0;
        } else if (ClickableView->Pressed) {
            textView->TextColor = theme.getColorForegroundPrimaryOnAccent();
            backgroundView->Color = theme.getColorAccentDark();
        } else if (ClickableView->Hovered || control.Focused) {
            textView->TextColor = theme.getColorForegroundPrimaryOnAccent();
            backgroundView->Color = theme.getColorAccent();
        } else {
            textView->TextColor = theme.getColorForegroundPrimaryOnAccent();
            backgroundView->Color = theme.getColorAccent();
        }
        border->Color = 0;
    }
    
    void TextButtonLayout::init() {
        __super::init();
        stack = ghnew StackLayout();
        textView->Font = theme.getButtonFont();
        paddingContainer->Child = textView;
        paddingContainer->Padding.Vertical = 4;
        paddingContainer->Padding.Horizontal = 8;
        stack->PreferredSize.width = PreferredSize::Width::WRAP;
        stack->PreferredSize.height = PreferredSize::Height::WRAP;
        stack->Children = { backgroundView, border, paddingContainer };
        ClickableView->Child = stack;
        root = ClickableView;
    }
}