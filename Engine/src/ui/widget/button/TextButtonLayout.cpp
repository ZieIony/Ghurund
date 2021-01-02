#include "TextButton.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {
    void TextButtonLayout::onStateChanged(Control& control) {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        if (!control.Enabled) {
            textView->TextColor = theme->getColorForegroundDisabledOnBackground();
            border->Color = theme->getColorForegroundDisabledOnBackground();
            backgroundView->Color = theme->getColorControlDisabled();
        } else if (ClickableView->Pressed || ClickableView->Hovered || control.Focused) {
            textView->TextColor = theme->getColorForegroundPrimaryOnBackground();
            border->Color = theme->getColorAccent();
            backgroundView->Color = theme->getColorControlNormal();
        } else {
            textView->TextColor = theme->getColorForegroundPrimaryOnBackground();
            border->Color = theme->getColorForegroundPrimaryOnBackground();
            backgroundView->Color = theme->getColorControlNormal();
        }
        clickResponseView->Pressed = ClickableView->Pressed;
    }

    void TextButtonFlatLayout::onStateChanged(Control& control) {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        if (!control.Enabled) {
            textView->TextColor = theme->getColorForegroundDisabledOnBackground();
            border->Color = 0;
        } else if (ClickableView->Pressed || ClickableView->Hovered || control.Focused) {
            textView->TextColor = theme->getColorForegroundPrimaryOnBackground();
            border->Color = theme->getColorAccent();
        } else {
            textView->TextColor = theme->getColorForegroundPrimaryOnBackground();
            border->Color = 0;
        }
        clickResponseView->Pressed = ClickableView->Pressed;
        backgroundView->Color = 0;
    }

    void TextButtonAccentLayout::onThemeChanged(Control& control) {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        textView->TextStyle = theme->TextStyles[Theme::TEXTSTYLE_BUTTON];
        clickResponseView->Color = theme->ColorHighlightOnAccent;
        border->Shape = ghnew RoundRect(control.Context->Graphics, 2.0f);
        clip->Shape = ghnew RoundRect(control.Context->Graphics, 2.0f);
        shadow->Shape = ghnew RoundRect(control.Context->Graphics, 2.0f);
    }

    void TextButtonAccentLayout::onStateChanged(Control& control) {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        if (!control.Enabled) {
            textView->TextColor = theme->getColorForegroundDisabledOnBackground();
            backgroundView->Color = 0;
        } else if (ClickableView->Pressed || ClickableView->Hovered || control.Focused) {
            textView->TextColor = theme->getColorForegroundPrimaryOnAccent();
            backgroundView->Color = theme->getColorAccent();
        } else {
            textView->TextColor = theme->getColorForegroundPrimaryOnAccent();
            backgroundView->Color = theme->ColorAccent;
        }
        clickResponseView->Pressed = ClickableView->Pressed;
        border->Color = 0;
    }

    void TextButtonLayout::init() {
        __super::init();
        stack = ghnew StackLayout();
        paddingContainer->Child = textView;
        paddingContainer->Padding.Vertical = 4;
        paddingContainer->Padding.Horizontal = 8;
        stack->PreferredSize.width = PreferredSize::Width::WRAP;
        stack->PreferredSize.height = PreferredSize::Height::WRAP;
        clickResponseView = makeShared<ClickResponseView>();
        stack->Children = { backgroundView, clickResponseView, paddingContainer };
        clip->Child = stack;
        StackLayoutPtr stack2 = ghnew StackLayout();
        stack2->PreferredSize.width = PreferredSize::Width::WRAP;
        stack2->PreferredSize.height = PreferredSize::Height::WRAP;
        stack2->Children = { shadow, clip, border };
        ClickableView->Child = stack2;
        root = ClickableView;
    }

    void TextButtonLayout::onThemeChanged(Control& control) {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        textView->TextStyle = theme->TextStyles[Theme::TEXTSTYLE_BUTTON];
        clickResponseView->Color = theme->ColorHighlightOnBackground;
    }
}