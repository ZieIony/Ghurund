#include "TextButton.h"
#include "ui/style/Theme.h"

#include "ui/LayoutLoader.h"

namespace Ghurund::UI {
    TextButtonDefaultLayout::TextButtonDefaultLayout(LayoutLoader& loader) {
        PointerList<Control*> controls;
        loader.load(FilePath(L"layouts/TextButtonDefaultLayout.xml"), controls);
        Root = controls[0];
        border = (Border*)Root->find(_T("border"));
        clip = (Clip*)Root->find(_T("clip"));
        shadow = (Shadow*)Root->find(_T("shadow"));
        paddingContainer = (Ghurund::UI::PaddingContainer*)Root->find(_T("padding"));
        clickableView = (Ghurund::UI::ClickableView*)Root->find(_T("clickable"));
        clickResponseView = (ClickResponseView*)Root->find(_T("clickResponse"));
        textView = (Ghurund::UI::TextBlock*)Root->find(_T("text"));
    }

    void TextButtonDefaultLayout::onThemeChanged(Control& control) {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        textView->TextStyle = theme->TextStyles[Theme::TEXTSTYLE_BUTTON];
        clickResponseView->Color = theme->ColorHighlightOnBackground;
    }

    void TextButtonDefaultLayout::onStateChanged(Control& control) {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        if (!control.Enabled) {
            textView->TextColor = theme->ColorForegroundDisabledOnBackground;
            border->Color = theme->ColorForegroundDisabledOnBackground;
            backgroundView->Color = theme->ColorControlDisabled;
        } else if (ClickableView->Pressed || ClickableView->Hovered || control.Focused) {
            textView->TextColor = theme->ColorForegroundPrimaryOnBackground;
            border->Color = theme->Colors[Theme::COLOR_ACCENT];
            backgroundView->Color = theme->ColorControlNormal;
        } else {
            textView->TextColor = theme->ColorForegroundPrimaryOnBackground;
            border->Color = 0;
            backgroundView->Color = theme->ColorControlNormal;
        }
    }

    TextButtonFlatLayout::TextButtonFlatLayout(LayoutLoader& loader) {
        PointerList<Control*> controls;
        loader.load(FilePath(L"layouts/TextButtonFlatLayout.xml"), controls);
        Root = controls[0];
        border = (Border*)Root->find(_T("border"));
        clip = (Clip*)Root->find(_T("clip"));
        paddingContainer = (Ghurund::UI::PaddingContainer*)Root->find(_T("padding"));
        clickableView = (Ghurund::UI::ClickableView*)Root->find(_T("clickable"));
        clickResponseView = (ClickResponseView*)Root->find(_T("clickResponse"));
        textView = (Ghurund::UI::TextBlock*)Root->find(_T("text"));
    }

    void TextButtonFlatLayout::onThemeChanged(Control& control) {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        textView->TextStyle = theme->TextStyles[Theme::TEXTSTYLE_BUTTON];
        clickResponseView->Color = theme->ColorHighlightOnBackground;
    }

    void TextButtonFlatLayout::onStateChanged(Control& control) {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        if (!control.Enabled) {
            textView->TextColor = theme->ColorForegroundDisabledOnBackground;
            border->Color = 0;
        } else if (ClickableView->Pressed || ClickableView->Hovered || control.Focused) {
            textView->TextColor = theme->ColorForegroundPrimaryOnBackground;
            border->Color = theme->Colors[Theme::COLOR_ACCENT];
        } else {
            textView->TextColor = theme->ColorForegroundPrimaryOnBackground;
            border->Color = 0;
        }
        backgroundView->Color = 0;
    }

    TextButtonAccentLayout::TextButtonAccentLayout(LayoutLoader& loader) {
        PointerList<Control*> controls;
        loader.load(FilePath(L"layouts/TextButtonAccentLayout.xml"), controls);
        Root = controls[0];
        clip = (Clip*)Root->find(_T("clip"));
        shadow = (Shadow*)Root->find(_T("shadow"));
        paddingContainer = (Ghurund::UI::PaddingContainer*)Root->find(_T("padding"));
        clickableView = (Ghurund::UI::ClickableView*)Root->find(_T("clickable"));
        clickResponseView = (ClickResponseView*)Root->find(_T("clickResponse"));
        textView = (Ghurund::UI::TextBlock*)Root->find(_T("text"));
    }

    void TextButtonAccentLayout::onThemeChanged(Control& control) {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        textView->TextStyle = theme->TextStyles[Theme::TEXTSTYLE_BUTTON];
        clickResponseView->Color = theme->ColorHighlightOnAccent;
        clip->Shape = ghnew RoundRect(control.Context->Graphics, 2.0f);
        shadow->Shape = ghnew RoundRect(control.Context->Graphics, 2.0f);
    }

    void TextButtonAccentLayout::onStateChanged(Control& control) {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        if (!control.Enabled) {
            textView->TextColor = theme->ColorForegroundDisabledOnBackground;
            backgroundView->Color = 0;
        } else if (ClickableView->Pressed || ClickableView->Hovered || control.Focused) {
            textView->TextColor = theme->ColorForegroundPrimaryOnAccent;
            backgroundView->Color = theme->Colors[Theme::COLOR_ACCENT];
        } else {
            textView->TextColor = theme->ColorForegroundPrimaryOnAccent;
            backgroundView->Color = theme->Colors[Theme::COLOR_ACCENT];
        }
    }
}