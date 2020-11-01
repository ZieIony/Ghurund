#include "TextBlockStyle.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    void TextBlockPrimaryStyle::onStateChanged(TextBlock& textView) const {
        textView.Font = theme.getPrimaryTextFont();
        if (!textView.Enabled) {
            textView.TextColor = theme.getColorForegroundDisabledOnBackground();
        } else {
            textView.TextColor = theme.getColorForegroundPrimaryOnBackground();
        }
    }

    void TextBlockSecondaryStyle::onStateChanged(TextBlock& textView) const {
        textView.Font = theme.getSecondaryTextFont();
        if (!textView.Enabled) {
            textView.TextColor = theme.getColorForegroundDisabledOnBackground();
        } else {
            textView.TextColor = theme.getColorForegroundSecondaryOnBackground();
        }
    }

    void TextBlockHeaderStyle::onStateChanged(TextBlock& textView) const {
        textView.Font = theme.getSecondaryTextFont();
        if (!textView.Enabled) {
            textView.TextColor = theme.getColorForegroundDisabledOnBackground();
        } else {
            textView.TextColor = theme.getColorForegroundSecondaryOnBackground();
        }
    }
}