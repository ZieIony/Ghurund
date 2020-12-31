#include "TextBlockStyle.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    void TextBlockPrimaryStyle::onThemeChanged(TextBlock& textView) const {
        Ghurund::UI::Theme* theme = textView.Theme;
        if (!theme)
            return;
        textView.TextStyle = theme->TextStyles[Theme::TEXTSTYLE_TEXT_PRIMARY];
    }

    void TextBlockPrimaryStyle::onStateChanged(TextBlock& textView) const {
        Ghurund::UI::Theme* theme = textView.Theme;
        if (!theme)
            return; 
        if (!textView.Enabled) {
            textView.TextColor = theme->ColorForegroundDisabledOnBackground;
        } else {
            textView.TextColor = theme->ColorForegroundPrimaryOnBackground;
        }
    }

    void TextBlockSecondaryStyle::onThemeChanged(TextBlock& textView) const {
        Ghurund::UI::Theme* theme = textView.Theme;
        if (!theme)
            return;
        textView.TextStyle = theme->TextStyles[Theme::TEXTSTYLE_TEXT_SECONDARY];
    }

    void TextBlockSecondaryStyle::onStateChanged(TextBlock& textView) const {
        Ghurund::UI::Theme* theme = textView.Theme;
        if (!theme)
            return;
        if (!textView.Enabled) {
            textView.TextColor = theme->getColorForegroundDisabledOnBackground();
        } else {
            textView.TextColor = theme->getColorForegroundSecondaryOnBackground();
        }
    }

    void TextBlockHeaderStyle::onThemeChanged(TextBlock& textView) const {
        Ghurund::UI::Theme* theme = textView.Theme;
        if (!theme)
            return;
        textView.TextStyle = theme->TextStyles[Theme::TEXTSTYLE_TEXT_SECONDARY];
    }

    void TextBlockHeaderStyle::onStateChanged(TextBlock& textView) const {
        Ghurund::UI::Theme* theme = textView.Theme;
        if (!theme)
            return;
        if (!textView.Enabled) {
            textView.TextColor = theme->getColorForegroundDisabledOnBackground();
        } else {
            textView.TextColor = theme->getColorForegroundSecondaryOnBackground();
        }
    }
}