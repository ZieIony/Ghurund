#include "ghuipch.h"
#include "TextBlockStyle.h"

#include "ui/style/Theme.h"

namespace Ghurund::UI {
    void TextBlockButtonStyle::onThemeChanged(Control& control) const {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        ((TextBlock&)control).TextFormat = theme->TextFormats[Theme::TEXTFORMAT_BUTTON];
    }

    void TextBlockButtonStyle::onStateChanged(Control& control) const {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        if (!control.Enabled) {
            ((TextBlock&)control).TextColor = theme->Colors[Theme::COLOR_DISABLED_ONBACKGROUND];
        } else {
            ((TextBlock&)control).TextColor = theme->Colors[Theme::COLOR_PRIMARY_ONBACKGROUND];
        }
    }

    void TextBlockPrimaryStyle::onThemeChanged(Control& control) const {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        ((TextBlock&)control).TextFormat = theme->TextFormats[Theme::TEXTFORMAT_TEXT_PRIMARY];
    }

    void TextBlockPrimaryStyle::onStateChanged(Control& control) const {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        if (!control.Enabled) {
            ((TextBlock&)control).TextColor = theme->Colors[Theme::COLOR_DISABLED_ONBACKGROUND];
        } else {
            ((TextBlock&)control).TextColor = theme->Colors[Theme::COLOR_PRIMARY_ONBACKGROUND];
        }
    }

    void TextBlockSecondaryStyle::onThemeChanged(Control& control) const {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        ((TextBlock&)control).TextFormat = theme->TextFormats[Theme::TEXTFORMAT_TEXT_SECONDARY];
    }

    void TextBlockSecondaryStyle::onStateChanged(Control& control) const {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        if (!control.Enabled) {
            ((TextBlock&)control).TextColor = theme->Colors[Theme::COLOR_DISABLED_ONBACKGROUND];
        } else {
            ((TextBlock&)control).TextColor = theme->Colors[Theme::COLOR_SECONDARY_ONBACKGROUND];
        }
    }

    void TextBlockHeaderStyle::onThemeChanged(Control& control) const {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        ((TextBlock&)control).TextFormat = theme->TextFormats[Theme::TEXTFORMAT_LIST_HEADER];
    }

    void TextBlockHeaderStyle::onStateChanged(Control& control) const {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        if (!control.Enabled) {
            ((TextBlock&)control).TextColor = theme->Colors[Theme::COLOR_DISABLED_ONBACKGROUND];
        } else {
            ((TextBlock&)control).TextColor = theme->Colors[Theme::COLOR_SECONDARY_ONBACKGROUND];
        }
    }

    void TextBlockButtonOnAccentStyle::onStateChanged(Control& control) const {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        if (!control.Enabled) {
            ((TextBlock&)control).TextColor = theme->Colors[Theme::COLOR_DISABLED_ONACCENT];
        } else {
            ((TextBlock&)control).TextColor = theme->Colors[Theme::COLOR_PRIMARY_ONACCENT];
        }
    }

    void TextBlockPrimaryOnAccentStyle::onStateChanged(Control& control) const {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        if (!control.Enabled) {
            ((TextBlock&)control).TextColor = theme->Colors[Theme::COLOR_DISABLED_ONACCENT];
        } else {
            ((TextBlock&)control).TextColor = theme->Colors[Theme::COLOR_PRIMARY_ONACCENT];
        }
    }

    void TextBlockSecondaryOnAccentStyle::onStateChanged(Control& control) const {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        if (!control.Enabled) {
            ((TextBlock&)control).TextColor = theme->Colors[Theme::COLOR_DISABLED_ONACCENT];
        } else {
            ((TextBlock&)control).TextColor = theme->Colors[Theme::COLOR_SECONDARY_ONACCENT];
        }
    }

    void TextBlockHeaderOnAccentStyle::onStateChanged(Control& control) const {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        if (!control.Enabled) {
            ((TextBlock&)control).TextColor = theme->Colors[Theme::COLOR_DISABLED_ONACCENT];
        } else {
            ((TextBlock&)control).TextColor = theme->Colors[Theme::COLOR_SECONDARY_ONACCENT];
        }
    }
}