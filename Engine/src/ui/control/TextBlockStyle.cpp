#include "TextBlockStyle.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    void TextBlockPrimaryStyle::onThemeChanged(TextBlock& textView) const {
        Ghurund::UI::Theme* theme = textView.Theme;
        if (!theme)
            return;
        textView.Font = theme->PrimaryTextFont;
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
        textView.Font = theme->SecondaryTextFont;
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
        textView.Font = theme->SecondaryTextFont;
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