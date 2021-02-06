#include "TextBlockStyle.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {
    void TextBlockButtonStyle::onThemeChanged(Control& control) const {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        ((TextBlock&)control).TextStyle = theme->TextStyles[Theme::TEXTSTYLE_BUTTON];
    }

    void TextBlockButtonStyle::onStateChanged(Control& control) const {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        if (!control.Enabled) {
            ((TextBlock&)control).TextColor = theme->ColorForegroundDisabledOnBackground;
        } else {
            ((TextBlock&)control).TextColor = theme->ColorForegroundPrimaryOnBackground;
        }
    }

    void TextBlockPrimaryStyle::onThemeChanged(Control& control) const {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        ((TextBlock&)control).TextStyle = theme->TextStyles[Theme::TEXTSTYLE_TEXT_PRIMARY];
    }

    void TextBlockPrimaryStyle::onStateChanged(Control& control) const {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        if (!control.Enabled) {
            ((TextBlock&)control).TextColor = theme->ColorForegroundDisabledOnBackground;
        } else {
            ((TextBlock&)control).TextColor = theme->ColorForegroundPrimaryOnBackground;
        }
    }

    void TextBlockSecondaryStyle::onThemeChanged(Control& control) const {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        ((TextBlock&)control).TextStyle = theme->TextStyles[Theme::TEXTSTYLE_TEXT_SECONDARY];
    }

    void TextBlockSecondaryStyle::onStateChanged(Control& control) const {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        if (!control.Enabled) {
            ((TextBlock&)control).TextColor = theme->ColorForegroundDisabledOnBackground;
        } else {
            ((TextBlock&)control).TextColor = theme->ColorForegroundSecondaryOnBackground;
        }
    }

    void TextBlockHeaderStyle::onThemeChanged(Control& control) const {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        ((TextBlock&)control).TextStyle = theme->TextStyles[Theme::TEXTSTYLE_LIST_HEADER];
    }

    void TextBlockHeaderStyle::onStateChanged(Control& control) const {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        if (!control.Enabled) {
            ((TextBlock&)control).TextColor = theme->ColorForegroundDisabledOnBackground;
        } else {
            ((TextBlock&)control).TextColor = theme->ColorForegroundSecondaryOnBackground;
        }
    }
}