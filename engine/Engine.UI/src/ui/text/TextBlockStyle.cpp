#include "ghuipch.h"
#include "TextBlockStyle.h"

#include "ui/style/Theme.h"

namespace Ghurund::UI {
    void TextBlockButtonStyle::apply(Control& control) const {
        auto format = TextFormatRef(Theme::TEXTFORMAT_BUTTON);
        ((TextBlock&)control).TextFormat = &format;
    }

    void TextBlockButtonStyle::onStateChanged(Control& control) const {
        if (!control.Enabled) {
            ((TextBlock&)control).TextColor = ColorRef(Theme::COLOR_DISABLED_ONBACKGROUND);
        } else {
            ((TextBlock&)control).TextColor = ColorRef(Theme::COLOR_PRIMARY_ONBACKGROUND);
        }
    }

    void TextBlockPrimaryStyle::apply(Control& control) const {
        auto format = TextFormatRef(Theme::TEXTFORMAT_TEXT_PRIMARY);
        ((TextBlock&)control).TextFormat = &format;
    }

    void TextBlockPrimaryStyle::onStateChanged(Control& control) const {
        if (!control.Enabled) {
            ((TextBlock&)control).TextColor = ColorRef(Theme::COLOR_DISABLED_ONBACKGROUND);
        } else {
            ((TextBlock&)control).TextColor = ColorRef(Theme::COLOR_PRIMARY_ONBACKGROUND);
        }
    }

    void TextBlockSecondaryStyle::apply(Control& control) const {
        auto format = TextFormatRef(Theme::TEXTFORMAT_TEXT_SECONDARY);
        ((TextBlock&)control).TextFormat = &format;
    }

    void TextBlockSecondaryStyle::onStateChanged(Control& control) const {
        if (!control.Enabled) {
            ((TextBlock&)control).TextColor = ColorRef(Theme::COLOR_DISABLED_ONBACKGROUND);
        } else {
            ((TextBlock&)control).TextColor = ColorRef(Theme::COLOR_SECONDARY_ONBACKGROUND);
        }
    }

    void TextBlockHeaderStyle::apply(Control& control) const {
        auto format = TextFormatRef(Theme::TEXTFORMAT_LIST_HEADER);
        ((TextBlock&)control).TextFormat = &format;
    }

    void TextBlockHeaderStyle::onStateChanged(Control& control) const {
        if (!control.Enabled) {
            ((TextBlock&)control).TextColor = ColorRef(Theme::COLOR_DISABLED_ONBACKGROUND);
        } else {
            ((TextBlock&)control).TextColor = ColorRef(Theme::COLOR_SECONDARY_ONBACKGROUND);
        }
    }

    void TextBlockButtonOnAccentStyle::onStateChanged(Control& control) const {
        if (!control.Enabled) {
            ((TextBlock&)control).TextColor = ColorRef(Theme::COLOR_DISABLED_ONACCENT);
        } else {
            ((TextBlock&)control).TextColor = ColorRef(Theme::COLOR_PRIMARY_ONACCENT);
        }
    }

    void TextBlockPrimaryOnAccentStyle::onStateChanged(Control& control) const {
        if (!control.Enabled) {
            ((TextBlock&)control).TextColor = ColorRef(Theme::COLOR_DISABLED_ONACCENT);
        } else {
            ((TextBlock&)control).TextColor = ColorRef(Theme::COLOR_PRIMARY_ONACCENT);
        }
    }

    void TextBlockSecondaryOnAccentStyle::onStateChanged(Control& control) const {
        if (!control.Enabled) {
            ((TextBlock&)control).TextColor = ColorRef(Theme::COLOR_DISABLED_ONACCENT);
        } else {
            ((TextBlock&)control).TextColor = ColorRef(Theme::COLOR_SECONDARY_ONACCENT);
        }
    }

    void TextBlockHeaderOnAccentStyle::onStateChanged(Control& control) const {
        if (!control.Enabled) {
            ((TextBlock&)control).TextColor = ColorRef(Theme::COLOR_DISABLED_ONACCENT);
        } else {
            ((TextBlock&)control).TextColor = ColorRef(Theme::COLOR_SECONDARY_ONACCENT);
        }
    }
}